#ifndef COMMANDER_H
#define COMMANDER_H

#include <string>
#include <vector>

#include "Army.h"
#include "Battle.h"
#include "Group.h"
#include "Warriors.h"

class Commander {
 private:
  std::string name_;
  float attack_skill_;
  float defence_skill_;
  float leadership_skill_;
  float strategy_skill_;

 public:
  Commander(std::string name, float attack_skill, float defence_skill, float leadership_skill, float strategy_skill);

  void TakePartInBattle();  // метод для участия в битве (поднятие морали + боевая единица)

  float CalculateAttackScore(Group& self, Group& enemy);
  float CalculateDefendScore(Group& self, Group& enemy);
  float CalculateRegroupScore(Group& self, Group& enemy);
  float CalculateCounterAttackScore(Group& self, Group& enemy);
  float CalculateRetreatScore(Group& self, Group& enemy);

  void MakeDecision(Group& self, Group& enemy);  // метод для принятия решения в битве
  void CommandGroup(Group& group);               // метод для управления группой

  std::string GetName() const { return name_; }
  float GetAttackSkill() const { return attack_skill_; }
  float GetDefenceSkill() const { return defence_skill_; }
  float GetLeadershipSkill() const { return leadership_skill_; }
  float GetStrategySkill() const { return strategy_skill_; }

  void SetName(const std::string& name) { name_ = name; }
  void SetAttackSkill(float skill) { attack_skill_ = skill; }
  void SetDefenceSkill(float skill) { defence_skill_ = skill; }
  void SetLeadershipSkill(float skill) { leadership_skill_ = skill; }
  void SetStrategySkill(float skill) { strategy_skill_ = skill; }
};

#endif
