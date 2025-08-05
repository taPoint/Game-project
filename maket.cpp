#include <vector>
#include <string>

class Army {
  std::string army_name_;
  int total_num_of_troops_;

  short num_of_groups_;
  std::vector<Group> groups_;
};

class Group {
 private:
  std::string group_name_;
  int num_of_troops_;
  std::vector<Warriors> vec_warriors_;
  Commander commander_;
  short morale_;

 public:

  int GetSize() { return num_of_troops_; }
  int GetMorale() { return morale_; }
  Commander GetCommander() { return commander_; }
  void AddNumOfTroops(int num) { num_of_troops_ += num; }
  Warriors* FindWarriorType(Warriors* warriors) {}

  void AddWarriors(Warriors* warriors, int num) {
    // AddNumOfTroops(warriors.num_of_warriors_);

    Warriors* added_warrior = FindWarriorType(warriors);
    if (added_warrior) {
      added_warrior -> num_of_warriors_ += num;
    } else {
      warriors.num_of_warriors_ = num;
      vec_warriors_.push_back(warriors);
    }
    warriors.num_of_warriors_ -= num;
  }

  void AddMorale(int num) { morale_ += num; }
  void AddCommander(Commander commander) { commander_ = commander; }

  void Attack() {
    
  }
  void Defence() {

  }
};

class Commander {
  short attack_skill_;
  short defence_skill_;

  void TakePartInBattle();
  void SetAttackSkill(short skill) { attack_skill_ = skill; }
  void SetDefenceSkill(short skill) { defence_skill_ = skill; }
};

class Warriors {
 public:
  std::string type_of_warrior_;
  short num_of_warriors_;
  short hp_;
  short damage_;
  short armor_;

  void SetNumOfWarriors(short num) { num_of_warriors_ = num; }
};

class Battle {
  short type_of_terrain_;

  void Fight(Group attack_group, Group defending_group) {
    int battle_duration = CalculateBattleDuration(attack_group, defending_group);

    for (int i = 0; i < battle_duration; i++) {
    }
  }

  int CalculateBattleDuration(Group first, Group second) {
    float ratio = std::min(first.GetSize(), second.GetSize()) / float(std::max(first.GetSize(), second.GetSize()));
    int base_time = 10;
    return static_cast<int>(base_time * ratio);
  }

};

class System {
  Army first_army;
  Army second_army;
  Battle battle; // передаю f s арми
  
  
};