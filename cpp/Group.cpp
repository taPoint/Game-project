#include <random>

#include "../include/Army.h"
#include "../include/Battle.h"
#include "../include/Commander.h"
#include "../include/Warriors.h"

float Group::GetMoraleModifier() {
  float modifier = 0;
  if (morale_ >= 50) {
    if (morale_ < 65) {
      modifier = 1;
    } else if (morale_ < 80) {
      modifier = 1.1;
    } else if (morale_ < 90) {
      modifier = 1.2;
    } else if (morale_ <= 100) {
      modifier = 1.3;
    }

  } else {
    if (morale_ >= 40) {
      modifier = 0.9;
    } else if (morale_ >= 30) {
      modifier = 0.8;
    } else if (morale_ >= 20) {
      modifier = 0.7;
    } else if (morale_ >= 10) {
      modifier = 0.6;
    } else if (morale_ >= 0) {
      modifier = 0.5;
    }
  }
  return modifier;
}

float Group::GetOrganisationModifier() {
  float modifier = 0;
  if (morale_ >= 50) {
    if (morale_ < 65) {
      modifier = 1;
    } else if (morale_ < 80) {
      modifier = 1;
    } else if (morale_ <= 100) {
      modifier = 1.1;
    }
  } else {
    if (morale_ >= 40) {
      modifier = 0.9;
    } else if (morale_ >= 30) {
      modifier = 0.75;
    } else if (morale_ >= 20) {
      modifier = 0.6;
    } else if (morale_ >= 10) {
      modifier = 0.4;
    } else if (morale_ >= 0) {
      modifier = 0.2;
    }
  }
  return modifier;
}

float Group::CalculateGroupStrength() {
  float strength = 0;
  for (size_t i = 0; i < vec_warriors_.size(); i++) {
    Warriors warrior_type = vec_warriors_[i];
    strength += warrior_type.damage_;
    strength += warrior_type.defence_;
    strength += warrior_type.hp_;
    strength *= warrior_type.num_of_warriors_;
    strength *= warrior_type.skill_;
  }
  return strength * GetMoraleModifier() - (strength - strength * GetOrganisationModifier());
}

float Group::CalculateAttackScore(Group& enemy) {
  float score = 0;
  score += morale_ - enemy.morale_;
  score += organisation_ - enemy.organisation_;
  score *= CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= commander_.GetAttackSkill();
  return score <= 0 ? 0 : score;
}

float Group::CalculateDefendScore(Group& enemy) {
  float score = 0;
  score -= morale_ - enemy.morale_;
  score -= organisation_ - enemy.organisation_;
  score /= CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= commander_.GetDefenceSkill();
  return score <= 0 ? 0 : score;
}

float Group::CalculateRegroupScore(Group& enemy) {
  float score = 0;
  score -= morale_ - enemy.morale_;
  score -= organisation_ - enemy.organisation_;
  score *= CalculateGroupStrength() / enemy.CalculateGroupStrength();
  return score <= 0 ? 0 : score;
}

float Group::CalculateCounterAttackScore(Group& enemy) {
  float score = 0;
  score += morale_ + enemy.morale_;
  score += organisation_ - enemy.organisation_;
  score *= CalculateGroupStrength() / enemy.CalculateGroupStrength();
  score *= commander_.GetAttackSkill();
  return score <= 0 ? 0 : score;
}

float Group::CalculateRetreatScore(Group& enemy) {
  float score = 0;
  score -= morale_ + enemy.morale_;
  score -= organisation_ + enemy.organisation_;
  score /= CalculateGroupStrength() / (2 * enemy.CalculateGroupStrength());
  return score <= 0 ? 0 : score;
}

float Group::CalculateInitiativeScore() {}

short Group::CompareGroups(Group& first, Group& second) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  float random_value = dis(gen);

  float first_iniative_score = first.CalculateInitiativeScore();
  float second_iniative_score = second.CalculateInitiativeScore();

  float sum = first_iniative_score + second_iniative_score;
  float first_iniative_probability = first_iniative_score / sum;
  float second_iniative_probability = second_iniative_probability / sum;

  short iniative = 0;

  if (random_value < first_iniative_probability) {
    iniative = 1;
  } else {
    iniative = 0;
  }

  return iniative;
}

void Group::ReduceWarriors(Warriors& warriors, float num) {
  num_of_troops_ -= num;
  
  if (warriors.num_of_warriors_ == num) {
    vec_warriors_.pop_back();
  } else {
    warriors.num_of_warriors_ -= num;
  }
}

// в будущем оптимизировать поменяв здесь float на short
void Group::TakeDamage(float damage) {
  // потом реализовать vec построения, где i = vec.size() это первые 1-2 ряда

  for (size_t i = vec_warriors_.size() - 1; i >= 0; i++) {

    // считаем общий хп в первой линии (или 2 рядах завтра пойму)
    float total_hp = vec_warriors_[i].num_of_warriors_ * vec_warriors_[i].hp_;
    short remaining_hp = static_cast<short>(total_hp) - static_cast<short>(damage);

    if (remaining_hp >= 0) {
      short num_of_deaths = remaining_hp / static_cast<short>(vec_warriors_[0].hp_);
      ReduceWarriors(vec_warriors_[i], num_of_deaths);
      break;
      // здесь надо добавить функцию отчёта о потерях и как то в будущем учитывать раненных
    } else {
      damage -= total_hp;
      ReduceWarriors(vec_warriors_[i], vec_warriors_[i].num_of_warriors_);
    }

  }
}

void Group::Attack(Group& enemy) {
  float total_damage = 0;

  for (size_t i = 0; i < vec_warriors_.size(); i++) {
    Warriors type_of_warriors = vec_warriors_[i];
    total_damage += type_of_warriors.damage_;
  }

  Commander enemy_commander = enemy.GetCommander();
  enemy_commander.MakeDefendDecision(enemy, *this);
}

void Group::Defend(Group& enemy) {
  // if допустим контратаковал то initiative = 0;
  float total_damage = 0;
  float total_defence = 0;
  float total_defenders_damage = 0;

  for (size_t i = 0; i < vec_warriors_.size(); i++) {
    Warriors type_of_warriors = vec_warriors_[i];
    total_defence += type_of_warriors.defence_;
    total_defenders_damage += type_of_warriors.damage_;
  }

  float ratio = total_defence / total_damage;
  float damage_done = total_damage - (total_defence);
  float retaliatory_damage_done = ;
}