#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>

#include "Army.h"
#include "Commander.h"
#include "Group.h"
#include "Warriors.h"

struct TypeOfTerrain {  // равнина, холмы, лес, мелководная река (каждая имеет своё количество очков преимущества)
  std::string terrain_under_first_group;
  std::string terrain_beetween_groups;
  std::string terrain_under_second_group;
};

struct BattleSituation {  // ситуация на поле боя обновляется у каждого командира каждый ход
  short organisation;     // 0-5
  short morale;           // 0-100
  short strength;         // Превосходим / Равны / Уступаем
  short advantage;        // позиционное преимущество (местность, укрепления, укрытия)
};

struct BattleResult {
  BattleSituation situation;
  int attack_losses;     // потери атакующей группы
  int defending_losses;  // потери обороняющейся группы
};

class Battle {
 private:
  std::string battle_name_;
  BattleResult result_;
  TypeOfTerrain terrain_;

 public:
  void Fight(Group first, Group second);
  int CalculateBattleDuration(Group first, Group second);
  BattleSituation GetBattleSituation(Group first, Group second);  // возвращает объект с ситуацией на поле боя (берёт
                                                                  // данные с групп, местности и из них стряпает объект)
  int DefineBattleSituation(Group first, Group second);
};

#endif