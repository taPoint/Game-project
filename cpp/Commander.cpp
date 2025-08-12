#include <random>

#include "../include/Army.h"
#include "../include/Battle.h"
#include "../include/Group.h"
#include "../include/Warriors.h"

Commander::Commander(std::string name, float attack_skill, float defence_skill, float leadership_skill,
                     float strategy_skill) {
  name_ = name;
  attack_skill_ = attack_skill;
  defence_skill_ = defence_skill;
  leadership_skill_ = leadership_skill;
  strategy_skill_ = strategy_skill;
}

void Commander::TakePartInBattle() {}

// std::string Commander::MakeDecision(Group& self, Group& enemy) {
//   float type_of_order = self.GetTypeOfOrder();
//   float group_power_ratio = self.CalculateGroupStrength() / enemy.CalculateGroupStrength();

//   // определяем число, соответствующее выбранному решению
//   std::random_device rd;                           // источник случайности
//   std::mt19937 gen(rd());                          // генератор случайных чисел
//   std::uniform_real_distribution<> dis(0.0, 1.0);  // диапазон [0, 1]
//   float random_value = dis(gen);                   // случайное значение от 0 до 1

//   if (type_of_order == 0 || group_power_ratio > 1) {
//     float attack_decision_score = CalculateAttackScore(self, enemy);
//     float defend_decision_score = CalculateDefendScore(self, enemy);
//     float regroup_decision_score = CalculateRegroupScore(self, enemy);

//     // нормируем вероятности (получаем вероятности от 0.0 до 1.0)
//     float sum = attack_decision_score + defend_decision_score + regroup_decision_score;
//     float attack_probability = attack_decision_score / sum;
//     float defend_probability = defend_decision_score / sum;
//     float regroup_probability = regroup_decision_score / sum;

//     if (random_value < attack_probability) {
//       self.Attack(enemy);
//     } else if (random_value < attack_probability + regroup_probability) {
//       self.Regroup(enemy);
//     } else {
//       if (type_of_order == 0) {
//         RequestDefense();
//         self.Regroup(enemy);
//       } else {
//         self.Defend(enemy);
//       }
//     }

//   } else if (type_of_order == 1 || group_power_ratio <= 1) {
//     float attack_decision_score = CalculateAttackScore(self, enemy);
//     float defend_decision_score = CalculateDefendScore(self, enemy);
//     float counter_attack_decision_score = CalculateCounterAttackScore(self, enemy);
//     float retreat_decision_score = CalculateRetreatScore(self, enemy);

//     float sum = attack_decision_score + defend_decision_score + counter_attack_decision_score +
//     retreat_decision_score; float attack_probability = attack_decision_score / sum; float defend_probability =
//     defend_decision_score / sum; float counter_attack_probability = counter_attack_decision_score / sum; float
//     retreat_probability = retreat_decision_score / sum;

//   } else {
//     self.Retreat(enemy);
//   }
//   return " ";
// }

std::string Commander::MakeAttackDecision(Group& self, Group& enemy) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  float random_value = dis(gen);

  std::string decision = 0;

  float attack_decision_score = self.CalculateAttackScore(enemy);
  float defend_decision_score = self.CalculateDefendScore(enemy);
  float regroup_decision_score = self.CalculateRegroupScore(enemy);

  float sum = attack_decision_score + defend_decision_score + regroup_decision_score;
  float attack_probability = attack_decision_score / sum;
  float defend_probability = defend_decision_score / sum;
  float regroup_probability = regroup_decision_score / sum;

  // представим вероятность как:
  // от 0 до attack_probability - атака
  // от attack_probabilty до attack_probabilty + regroup_probability - перегруппировка
  // от attack_probabilty + regroup_probability до 1 - оборона
  if (random_value < attack_probability) {
    decision = "Наступление";
    self.Attack(enemy);
  } else if (random_value < attack_probability + regroup_probability) {
    decision = "Перегруппировка";
    self.Regroup(enemy);
  } else {
    decision = "Переход к обороне";
    self.Defend(enemy);
  }

  return decision;
}

std::string Commander::MakeDefendDecision(Group& self, Group& enemy) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  float random_value = dis(gen);

  std::string decision = 0;

  float attack_decision_score = self.CalculateAttackScore(enemy);
  float defend_decision_score = self.CalculateDefendScore(enemy);
  float counter_attack_decision_score = self.CalculateCounterAttackScore(enemy);
  float retreat_decision_score = self.CalculateRetreatScore(enemy);

  float sum = attack_decision_score + defend_decision_score + counter_attack_decision_score + retreat_decision_score;
  float attack_probability = attack_decision_score / sum;
  float defend_probability = defend_decision_score / sum;
  float counter_attack_probability = counter_attack_decision_score / sum;
  float retreat_probability = retreat_decision_score / sum;

  // представим вероятность как:
  // от 0 до defend_probability - оборона
  // от defend_probability до defend_probability + counter_attack_probability - контратака
  // от defend_probability + counter_attack_prob до 1 - отступление
  if (random_value < defend_probability) {
    decision = "Оборона";
    self.Defend(enemy);
  } else if (random_value < defend_probability + counter_attack_probability) {
    decision = "Контратака";
    self.CounterAttack(enemy);
  } else {
    decision = "Отступление";
    self.Retreat(enemy);
  }
}

void Commander::CommandGroup(Group& self, Group& enemy, short& initiative) {
  // функция выбора решения исходя из положения (атакующий/обороняющий)
  // float group_power_ratio = self.CalculateGroupStrength() / enemy.CalculateGroupStrength();

  if (initiative == 1) {
    // принимает решение в положении атакующего
    MakeAttackDecision(
        self,
        enemy);  // приняв решение, в функции этого решения вызывается функция вызова принятия решения для противника
  } else {
    // принимает решение в положении обороняющегося
    MakeDefendDecision(self, enemy);
  }
}
