#include "actor.h"
#include "battlefield.h"


RainyActor::RainyActor() {
    this->attr["revivalPotion"] = 1;
}

std::vector<Pet_T> RainyActor::ChooseStartingPet() {
    // TODO: 返回雨天队的出场宠物
}

Action_T RainyActor::ChooseAction() {
    // TODO: 返回选取的动作
}

Pet_T RainyActor::ChoosePet(bool active) {
    // TODO: 返回即将交换上场的宠物
}

Skill_T RainyActor::ChooseSkill() {
    // TODO: 选择场上宠物使用的技能
}


PotionInfo RainyActor::ChoosePotion() {
    // TODO: 返回使用的药剂
}

std::string RainyActor::GetName() {
    return "Enemy";//"Rainy Team";
}

