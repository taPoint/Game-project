#ifndef USERDATA_h
#define USERDATA_H

#include "Army.h"
#include "Battle.h"
#include "Commander.h"
#include "Warriors.h"

class UserData {
 private:
  std::string username_;
  std::vector<Army> armies_;
  std::vector<Group> groups_;
  std::vector<Warriors> warriors_;

 public:
  UserData(std::string username) : username_(username) {}

  void AddArmy(const Army& army);

  void AddGroup(const Group& group);

  void AddWarrior(const Warriors& warrior);

  std::string GetUsername() const { return username_; }
};

#endif