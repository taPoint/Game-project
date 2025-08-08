#include "../include/Army.h"
#include "../include/Battle.h"
#include "../include/Group.h"
#include "../include/Warriors.h"

Commander::Commander(std::string name, short attack_skill, short defence_skill, short leadership_skill,
                     short strategy_skill) {
  name_ = name;
  attack_skill_ = attack_skill;
  defence_skill_ = defence_skill;
  leadership_skill_ = leadership_skill;
  strategy_skill_ = strategy_skill;
}

void Commander::TakePartInBattle() {}

void Commander::MakeDecision(BattleSituation& situation) {
  // если в положении атакующего:
  // получаем объект BattleSituation
  float attack_decision_score = CalculateAttackDecisionScore(situation);
  float defend_decision_score = CalculateDefendDecisionScore(situation);
  float regroup_decision_score = CalculateRegroupDecisionScore(situation);

  float sum = attack_decision_score + defend_decision_score + regroup_decision_score;
  float attack_probability = attack_decision_score / sum;
  float defend_probability = defend_decision_score / sum;
  float regroup_probability = regroup_decision_score / sum;
}

void Commander::CommandGroup(Group& group) {
  // ща поймём вроде и без него как будто обойдёмся
}
