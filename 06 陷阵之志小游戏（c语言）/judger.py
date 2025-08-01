import argparse
import difflib
import os
import shutil
import subprocess
import sys
import tempfile

TASKS = [
    ('1_task1', ['actions.cpp', 'algorithms.cpp','engine.cpp','field.cpp','terrain.cpp','unit.cpp','main.cpp']),
    ('2_task2', ['actions.cpp', 'algorithms.cpp','engine.cpp','field.cpp','terrain.cpp','unit.cpp','main.cpp']),
    ('3_task3', ['actions.cpp', 'algorithms.cpp','engine.cpp','field.cpp','terrain.cpp','unit.cpp','main.cpp']),
    ('4_task4', ['actions.cpp', 'algorithms.cpp','engine.cpp','field.cpp','terrain.cpp','unit.cpp','main.cpp']),
]
TASK_NAMES = [n for n, _ in TASKS]
TASK_NAME_TO_I = {n: i for i, n in enumerate(TASK_NAMES)}
IN_SUFFIX = '.in'
OUT_SUFFIX = '.out'
OUT_WRONG_SUFFIX = '.out-wrong.txt'

class Skip(Exception):
    pass

class Wrong(Exception):
    def __init__(self, msg, extra_msg=(), score=0):
        self.msg = msg
        self.extra_msg = extra_msg
        self.score = score

    def __str__(self):
        return self.msg


def get_thisdir():
    return os.path.dirname(os.path.abspath(
        sys.executable if getattr(sys, 'frozen', False) else __file__
    ))


# cs1604_txt is the path of cs1604.txt
def get_cs1604_path(cs1604_txt):
    # cs1604_txt = os.path.join(thisdir, 'source', 'cs1604.txt')
    try:
        f = open(cs1604_txt,encoding='utf-8')
    except FileNotFoundError:
        print(
            'error: to use StanfordCppLib, you must create a text file',
            cs1604_txt,
            'whose contents is the absolute path '
            'to the compiled StanfordCppLib.',
            sep='\n', file=sys.stderr
        )
        sys.exit(1)
    with f:
        s = f.read().strip()
    if not os.path.isabs(s):
        print(
            'error: the path to StanfordCppLib must be an absolute path, but',
            s,
            'is supplied, which is not an absolute path.',
            sep='\n', file=sys.stderr
        )
        sys.exit(1)
    return s


def parse_args():
    thisdir = get_thisdir()

    case_choices = sorted(set(
        f.name[:-len(IN_SUFFIX)]
        for task in TASK_NAMES
        for f in os.scandir(os.path.join(thisdir, 'data', task))
        if f.is_file() and f.name.endswith(IN_SUFFIX)
    ))

    parser = argparse.ArgumentParser()
    parser.add_argument(
        '-T', '--task', type=TASK_NAME_TO_I.__getitem__, action='append',
        choices=TASK_NAMES,
        help='problem to judge (defaults to all)'
    )
    for i, task in enumerate(TASK_NAMES):
        parser.add_argument(
            f'-{i + 1}', dest='task', action='append_const', const=i,
            help=f'same as --task {task}'
        )
    parser.add_argument(
        '-c', '--case', action='append', choices=case_choices,
        help='sample input/output to test against (defaults to all)'
    )
    parser.add_argument(
        '--timeout', default=1, type=int,
        help='time limit for each invocation of your program, in seconds'
    )
    # parser.add_argument(
    #     '--cs1604', action='store_true',
    #     help='use StanfordCppLib pointed to by source/cs1604.txt'
    # )
    args = parser.parse_args()

    if args.task is None:
        args.task = list(range(len(TASKS)))
    else:
        args.task = sorted(set(args.task))

    if args.case is None:
        args.case = case_choices.copy()
    else:
        args.case = sorted(set(args.case))

    cs1604_txt = os.path.join(thisdir, 'source', 'cs1604.txt')
    if os.path.exists(cs1604_txt):
        cs1604_path = get_cs1604_path(cs1604_txt)
        args.cs1604_cxxargs = [f'-I{os.path.join(cs1604_path, "include")}']
        args.cs1604_ldargs = [
            f'-L{os.path.join(cs1604_path, "lib")}', '-lCS1604'
        ]
    else:
        args.cs1604_cxxargs = []
        args.cs1604_ldargs = []

    args.thisdir = thisdir

    return args


def standard_judger_readlines(f):
    result = [l.rstrip() for l in f]
    while result != [] and result[-1] == '':
        result.pop()
    return [l + '\n' for l in result]


DIFFER = difflib.Differ()

def standard_judger(fout, fstd):
    out = standard_judger_readlines(fout)
    std = standard_judger_readlines(fstd)
    diff = list(DIFFER.compare(std, out))
    if any(l[0] != ' ' for l in diff):
        raise Wrong('Incorrect output', ('[DIFF] ' + l for l in diff))


def judge(args, task, case, workdir, exe_path):
    task_name = TASK_NAMES[task]
    in_path, std_path = (
        os.path.join(args.thisdir, 'data', task_name, case + suffix)
        for suffix in (IN_SUFFIX, OUT_SUFFIX)
    )

    try:
        fin = open(in_path, mode='rb')
    except FileNotFoundError:
        raise Skip()
    with fin:
        fdout, out_path = tempfile.mkstemp(dir=workdir)
        try:
            subprocess.run(
                [exe_path], check=True, timeout=args.timeout,
                stdin=fin, stdout=fdout
            )
        except subprocess.TimeoutExpired:
            raise Wrong('Timed out')
        except subprocess.CalledProcessError as e:
            raise Wrong(
                f'Runtime error with return code '
                f'{e.returncode} ({e.returncode:#x})'
            )

    try:
        with open(out_path) as fout:
            with open(std_path) as fstd:
                standard_judger(fout, fstd)
    except Wrong as e:
        if e.score == 0:
            try:
                dst_path = os.path.join(
                    args.thisdir, f'{task_name}.{case}{OUT_WRONG_SUFFIX}'
                )
                shutil.copy2(out_path, dst_path)
                e.msg = f'{e.msg} (output copied to {dst_path})'
            except OSError:
                pass
        raise e


def main():
    args = parse_args()
    for task in args.task:
        tc = None
        workdir = tempfile.mkdtemp()
        try:
            exe_path = compile_and_link(args, task, workdir)
            for case in args.case:
                tc = f'[T{TASK_NAMES[task][0]} c{case}]'
                try:
                    judge(args, task, case, workdir, exe_path)
                except Skip:
                    pass
                except Wrong as e:
                    print(tc, e.msg)
                    sys.stdout.writelines(f'{tc} {l}' for l in e.extra_msg)
                else:
                    print(tc, 'Correct')
        except Wrong as e:
            t = f'[T{TASK_NAMES[task][0]}]'
            print(t, e.msg)
            sys.stdout.writelines(f'{t} {l}' for l in e.extra_msg)
        except OSError as e:
            print(tc if tc else f'[T{TASK_NAMES[task][0]}]', end=' ')
            import traceback
            traceback.print_exception(e, file=sys.stdout)
        finally:
            shutil.rmtree(workdir, ignore_errors=True)


def compile_and_link(args, task, workdir):
    task_name, srcs = TASKS[task]
    src_paths = [
        os.path.join(args.thisdir, 'source', task_name, src)
        for src in srcs
    ]
    for src_path in src_paths:
        if not os.path.exists(src_path):
            raise Wrong(f'Missing source file {src_path}')
    obj_paths = [os.path.join(workdir, f'{src}.o') for src in srcs]
    try:
        for src_path, obj_path in zip(src_paths, obj_paths):
            subprocess.run(
                ['g++', '-Wall','-Wextra','-Wno-return-type', '-pedantic', '-std=c++11'] + args.cs1604_cxxargs
                + ['-c', src_path, '-o', obj_path],
                check=True
            )
    except subprocess.CalledProcessError as e:
        raise Wrong(f'Compile error on {src_path}')
    exe_path = os.path.join(workdir, task_name)
    try:
        subprocess.run(
            ['g++'] + obj_paths + args.cs1604_ldargs + ['-o', exe_path] + ['-std=c++11'],
            check=True
        )
    except subprocess.CalledProcessError:
        raise Wrong(
            "Link error (did you forget to define a function, "
            "or make a typo in the function's name, "
            "or mistake the function's signature?)"
        )
    return exe_path


if __name__ == '__main__':
    main()