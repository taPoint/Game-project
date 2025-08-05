#ifndef ARMY_H
#define ARMY_H

#include "Battle.h"
#include "Group.h"
#include "Commander.h"
#include "Warriors.h"

#include <string>
#include <vector>

class Army {
  std::string army_name_;
  int total_num_of_troops_;

  short num_of_groups_;
  std::vector<Group> groups_;
};

#endif