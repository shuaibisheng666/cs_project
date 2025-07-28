#include "actor.h"
#include "battlefield.h"


std::vector<Pet_T> SunnyActor::ChooseStartingPet() {
    // TODO: 返回晴天队的出场宠物
    // 晴天队有PGR，永远首发P
}

Action_T SunnyActor::ChooseAction() {
    // TODO: 返回选取的动作
}

Pet_T SunnyActor::ChoosePet(bool active) {
    // TODO: 返回即将交换上场的宠物
}

Skill_T SunnyActor::ChooseSkill() {
    // TODO: 选择场上宠物使用的技能
}

std::string SunnyActor::GetName() {
    return "Enemy";//"Sunny Team";
}
