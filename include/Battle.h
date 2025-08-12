#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>

#include "Army.h"
#include "Commander.h"
#include "Group.h"
#include "Warriors.h"

struct TypeOfTerrain {  // равнина, холмы, лес, мелководная река (каждая имеет своё количество очков преимущества)
  std::vector<short> terrain_;  // вектор с 10 значениями описывающий местность
};

struct ResulfOfDecision {};

struct BattleResult {
  int attack_losses;     // потери атакующей группы
  int defending_losses;  // потери обороняющейся группы
};

class Battle {
 private:
  std::string battle_name_;
  TypeOfTerrain terrain_;
  BattleResult result_;

 public:
  void Fight(Group& first, Group& second);
  void FightWithoutOrder(Group& first, Group& second);
  short CalculateBattleDuration(Group& first, Group& second);
};

#endif