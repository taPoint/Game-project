#include "../include/Army.h"
#include "../include/Battle.h"
#include "../include/Commander.h"
#include "../include/Warriors.h"

float Group::CalculateGroupStrength() {
  float strength = 0;
  for (size_t i = 0; i < vec_warriors_.size(); i++) {
    Warriors warrior_type = vec_warriors_[i];
    strength += warrior_type.damage_;
    strength += warrior_type.defence_;
    strength += warrior_type.hp_;
    strength *= warrior_type.num_of_warriors_;
    strength *= warrior_type.skill_;
  }
  strength *= commander_.GetAttackSkill();
  return strength;
}