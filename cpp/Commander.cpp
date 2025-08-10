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

float Commander::CalculateAttackScore(Group& self, Group& enemy) {
  float score = 0;
  score += self.GetMorale() - enemy.GetMorale();
  score += self.GetOrganisation() - enemy.GetOrganisation();
  score *= self.CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= attack_skill_;
  return score <= 0 ? 0 : score;
}

float Commander::CalculateDefendScore(Group& self, Group& enemy) {
  float score = 0;
  score -= self.GetMorale() + enemy.GetMorale();
  score -= self.GetOrganisation() + enemy.GetOrganisation();
  score /= self.CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= defence_skill_;
  return score <= 0 ? 0 : score;
}

float Commander::CalculateRegroupScore(Group& self, Group& enemy) {
  float score = 0;
  score += enemy.GetMorale() - self.GetMorale();
  score += enemy.GetOrganisation() - self.GetOrganisation();
  score /= self.CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= defence_skill_;
  return score <= 0 ? 0 : score;
}

float Commander::CalculateCounterAttackScore(Group& self, Group& enemy) {
  float score = 0;
  score += enemy.GetMorale() - self.GetMorale();
  score += enemy.GetOrganisation() - self.GetOrganisation();
  score /= self.CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= attack_skill_;
  return score <= 0 ? 0 : score;
}

float Commander::CalculateRetreatScore(Group& self, Group& enemy) {
  float score = 0;
  score += enemy.GetMorale() - self.GetMorale();
  score += enemy.GetOrganisation() - self.GetOrganisation();
  score /= self.CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= defence_skill_;
  return score <= 0 ? 0 : score;
}

void Commander::MakeDecision(Group& self, Group& enemy) {
  float type_of_order = self.GetTypeOfOrder();
  float group_power_ratio = self.CalculateGroupStrength() / enemy.CalculateGroupStrength();

  if (type_of_order == 0 || group_power_ratio > 1) {
    float attack_decision_score = CalculateAttackScore(self, enemy);
    float defend_decision_score = CalculateDefendScore(self, enemy);
    float regroup_decision_score = CalculateRegroupScore(self, enemy);

    // нормируем вероятности (получаем вероятности от 0.0 до 1.0)
    float sum = attack_decision_score + defend_decision_score + regroup_decision_score;
    float attack_probability = attack_decision_score / sum;
    float defend_probability = defend_decision_score / sum;
    float regroup_probability = regroup_decision_score / sum;

    // определяем число, соответствующее выбранному решению
    std::random_device rd;                           // источник случайности
    std::mt19937 gen(rd());                          // генератор случайных чисел
    std::uniform_real_distribution<> dis(0.0, 1.0);  // диапазон [0, 1]
    float random_value = dis(gen);                   // случайное значение от 0 до 1

    // представим вероятность как:
    // от 0 до attack_probability - атака
    // от attack_probabilty до attack_probabilty + regroup_probability - перегруппировка
    // от attack_probabilty + regroup_probability до 1 - оборона
    if (random_value < attack_probability) {
      self.Attack();
    } else if (random_value < attack_probability + regroup_probability) {
      self.Regroup();
    } else {
      if (type_of_order == 0) {
        RequestDefense();
        self.Regroup();
      } else {
        self.Defend();
      }
    }

  } else if (type_of_order == 1) {
    float attack_decision_score = CalculateAttackScore(self, enemy);
    float defend_decision_score = CalculateDefendScore(self, enemy);
    float counter_attack_decision_score = CalculateCounterAttackScore(self, enemy);
    float retreat_decision_score = CalculateRetreatScore(self, enemy);

    float sum = attack_decision_score + defend_decision_score + counter_attack_decision_score + retreat_decision_score;
    float attack_probability = attack_decision_score / sum;
    float defend_probability = defend_decision_score / sum;
    float counter_attack_probability = counter_attack_decision_score / sum;
    float retreat_probability = retreat_decision_score / sum;

  } else {
    self.Retreat();
  }
}

void Commander::CommandGroup(Group& group) {
  // ща поймём вроде и без него как будто обойдёмся
}
