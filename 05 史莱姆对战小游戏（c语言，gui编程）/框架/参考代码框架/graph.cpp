#include "graph.h"

GraphSlime::GraphSlime(Actor* left, Actor* right, BattleField* bf) {
    // TODO: ��ʼ��ͼ����
}

void GraphSlime::Update() {
    // TODO: ����ͼ�����е���������

    easy2d::SceneManager::enter(battle_scene);
    easy2d::Game::start();
    battle_scene->removeAllListeners();

    // ��Ϸ���к��������ؿ���̨��ͼ�񴰿��Դ��ڣ�
    easy2d::Timer::add([=]() {
        easy2d::Game::quit();
    }, 0);
}

easy2d::Sprite* GraphSlime::SetSlimeOnPitch(bool PorE, float x, float y) {  // ����PorE��ʾ��һ�з�
    // TODO: ����ʷ��ķͼƬ���������HPͼƬ��״̬ͼ��ĺ���
}

void GraphSlime::SetHPBar(easy2d::Sprite* slimeImg, int hp, int hpMax, float x, float y) {
    // TODO: ���HPͼƬ������HP���֣�
}

void GraphSlime::SetIcons(easy2d::Sprite* slimeImg, DefaultedMap<std::string, int, 0>& attr, float x, float y) {
    // TODO: ����״̬ͼ��
}

std::string GraphSlime::GetSlimeImg(const Pet* slime, bool PorE) {
    // TODO: ��ȡʷ��ķͼƬ���ļ���
}

GraphSlime::~GraphSlime() {
    delete battle_scene;
}
