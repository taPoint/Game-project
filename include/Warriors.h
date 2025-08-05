#ifndef WARRIORS_H
#define WARRIORS_H

#include "Battle.h"
#include "Army.h"
#include "Group.h"
#include "Commander.h"

#include <string>
#include <vector>

class Warriors {
 public:
  std::string type_of_warrior_;
  short num_of_warriors_;
  short hp_;
  short damage_;
  short armor_;

  void SetNumOfWarriors(short num) { num_of_warriors_ = num; }
};

#endif