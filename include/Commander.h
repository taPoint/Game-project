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
  short attack_skill_;
  short defence_skill_;
  short leadership_skill_;
  short strategy_skill_;

 public:
  Commander(std::string name, short attack_skill, short defence_skill, short leadership_skill, short strategy_skill);

  void TakePartInBattle();  // метод для участия в битве (поднятие морали + боевая единица)
  float CalculateAttackDecisionScore(BattleSituation situation);
  float CalculateDefendDecisionScore(BattleSituation situation);
  float CalculateRegroupDecisionScore(BattleSituation situation);
  void Attack(Group& group);
  void Defend(Group& group);
  void Regroup(Group& group);
  void CounterAttack(Group& group);
  void Retreat(Group& group);
  void MakeDecision(BattleSituation& situation);  // метод для принятия решения в битве
  void CommandGroup(Group& group);                // метод для управления группой во время боя

  std::string GetName() const { return name_; }
  short GetAttackSkill() const { return attack_skill_; }
  short GetDefenceSkill() const { return defence_skill_; }
  short GetLeadershipSkill() const { return leadership_skill_; }
  short GetStrategySkill() const { return strategy_skill_; }

  void SetName(const std::string& name) { name_ = name; }
  void SetAttackSkill(short skill) { attack_skill_ = skill; }
  void SetDefenceSkill(short skill) { defence_skill_ = skill; }
  void SetLeadershipSkill(short skill) { leadership_skill_ = skill; }
  void SetStrategySkill(short skill) { strategy_skill_ = skill; }
};

#endif
