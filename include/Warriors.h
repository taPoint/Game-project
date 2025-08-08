#ifndef WARRIORS_H
#define WARRIORS_H

#include <string>
#include <vector>

#include "Army.h"
#include "Battle.h"
#include "Commander.h"
#include "Group.h"

class Warriors {
 public:
  std::string type_of_warriors_;
  short num_of_warriors_;
  short hp_;
  short damage_;
  short defence_;

  void SetNumOfWarriors(short num) { num_of_warriors_ = num; }
};

#endif