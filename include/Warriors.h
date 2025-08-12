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
  float num_of_warriors_;
  float hp_;
  float damage_;
  float defence_;
  float skill_;

  void SetNumOfWarriors(short num) { num_of_warriors_ = num; }
};

#endif