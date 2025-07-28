#include "graph.h"

GraphSlime::GraphSlime(Actor* left, Actor* right, BattleField* bf) {
    // TODO: 初始化图像画面
}

void GraphSlime::Update() {
    // TODO: 更新图像画面中的所有内容

    easy2d::SceneManager::enter(battle_scene);
    easy2d::Game::start();
    battle_scene->removeAllListeners();

    // 游戏运行后立即返回控制台（图像窗口仍存在）
    easy2d::Timer::add([=]() {
        easy2d::Game::quit();
    }, 0);
}

easy2d::Sprite* GraphSlime::SetSlimeOnPitch(bool PorE, float x, float y) {  // 参数PorE表示玩家或敌方
    // TODO: 设置史莱姆图片，调用描绘HP图片和状态图标的函数
}

void GraphSlime::SetHPBar(easy2d::Sprite* slimeImg, int hp, int hpMax, float x, float y) {
    // TODO: 描绘HP图片（包括HP文字）
}

void GraphSlime::SetIcons(easy2d::Sprite* slimeImg, DefaultedMap<std::string, int, 0>& attr, float x, float y) {
    // TODO: 设置状态图标
}

std::string GraphSlime::GetSlimeImg(const Pet* slime, bool PorE) {
    // TODO: 获取史莱姆图片的文件名
}

GraphSlime::~GraphSlime() {
    delete battle_scene;
}
