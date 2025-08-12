#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

#include "Army.h"
#include "Battle.h"
#include "Commander.h"
#include "Warriors.h"

class Group {
 private:
  std::string group_name_;
  Commander commander_;
  float num_of_troops_;
  std::vector<Warriors> vec_warriors_;  // 1 ячейка - 1 тип войск (и их количество)
  float morale_;
  float organisation_;

 public:
  void Attack(Group& enemy);
  void Defend(Group& enemy);
  void Regroup(Group& enemy);
  void CounterAttack(Group& enemy);
  void Retreat(Group& enemy);

  float CalculateAttackScore(Group& enemy);
  float CalculateDefendScore(Group& enemy);
  float CalculateRegroupScore(Group& enemy);
  float CalculateCounterAttackScore(Group& enemy);
  float CalculateRetreatScore(Group& enemy);
  float CalculateGroupStrength();
  float CalculateInitiativeScore();

  static short CompareGroups(Group& first, Group& second);
  Warriors FindWarriorType(Warriors warriors);

  void TakeDamage(float damage);

  void AddNumOfTroops(float num) { num_of_troops_ += num; }
  void AddWarriors(Warriors warriors, float num);
  void ReduceWarriors(Warriors warriors, float num);
  void AddMorale(float num) { morale_ += num; }

  void SetGroupName(std::string& group_name) { group_name_ = group_name; }
  void SetCommander(Commander& commander) { commander_ = commander; }

  float GetMoraleModifier();
  float GetOrganisationModifier();
  float GetOrganisation() const { return organisation_; }
  float GetSize() const { return num_of_troops_; }
  float GetMorale() const { return morale_; }
  Commander GetCommander() const { return commander_; }
};

#endif