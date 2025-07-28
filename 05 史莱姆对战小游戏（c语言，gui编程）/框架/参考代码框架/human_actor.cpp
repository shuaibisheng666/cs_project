#include "actor.h"

#include <sstream>
#include <unordered_set>


HumanActor::HumanActor() {
    this->GetName();
}

std::vector<Pet_T> HumanActor::ChooseStartingPet() {
    // TODO: 从用户输入中得到上场的宠物
}

Action_T HumanActor::ChooseAction() {
    // TODO: 返回选取的动作
}

Pet_T HumanActor::ChoosePet(bool active) {
    // TODO: 返回即将交换上场的宠物
    // active 代表<主动交换宠物>or<场上宠物阵亡后被动交换宠物>
}

Skill_T HumanActor::ChooseSkill() {
    // TODO: 选择场上宠物使用的技能
}

std::string HumanActor::GetName() {
    return "You";
}
