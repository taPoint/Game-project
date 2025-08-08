#ifndef ARMY_H
#define ARMY_H

#include <string>
#include <vector>

#include "Battle.h"
#include "Commander.h"
#include "Group.h"
#include "Warriors.h"

class Army {
 private:
  std::string army_name_;
  int total_num_of_troops_;
  short num_of_groups_;
  std::vector<Group> groups_;

 public:
  Army(std::string name) : army_name_(name), total_num_of_troops_(0), num_of_groups_(0) {}

  void AddGroup(const Group& group) {
    groups_.push_back(group);
    // total_num_of_troops_ += group.GetSize();
    num_of_groups_++;
  }

  std::string GetArmyName() const { return army_name_; }
  int GetTotalNumOfTroops() const { return total_num_of_troops_; }
  short GetNumOfGroups() const { return num_of_groups_; }

  void Attack() {}
  void Defend() {}
};

#endif