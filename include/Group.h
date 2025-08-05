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
  int num_of_troops_;
  std::vector<Warriors> vec_warriors_;  // 1 ячейка - 1 тип войск
  short morale_;

 public:
  int GetSize() { return num_of_troops_; }
  int GetMorale() { return morale_; }
  Commander GetCommander() { return commander_; }

  void AddNumOfTroops(int num) { num_of_troops_ += num; }
  Warriors FindWarriorType(Warriors warriors) {}
  void AddWarriors(Warriors warriors, int num) {}
  void AddMorale(int num) { morale_ += num; }
  void AddCommander(Commander commander) { commander_ = commander; }

  void Attack() {}
  void Defence() {}
  void ChooseTactics() {}
};

#endif