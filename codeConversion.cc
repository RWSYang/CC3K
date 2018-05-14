#include "codeConversion.h"

using namespace std;

map<string, string> races = {
  {"h", "Human"},
  {"e", "Elf"},
  {"d", "Dwarf"},
  {"o", "Orc"}
};

map<string, int> racesInt = {
  {"Human", 0},
  {"Elf", 1},
  {"Dwarf", 2},
  {"Orc", 3}
};

map<int, string> intRaces = {
  {0, "Human"},
  {1, "Elf"},
  {2, "Dwarf"},
  {3, "Orc"}
};

std::map<std::string, std::string> directions = {
  {"no", "North"},
  {"so", "South"},
  {"ea", "East"},
  {"we", "West"},
  {"ne", "North East"},
  {"nw", "North West"},
  {"se", "South East"},
  {"sw", "South West"}
};

std::map<CM, std::string> enemies = {
  {CM::Werewolf, "Werewolf"},
  {CM::Vampire, "Vampire"},
  {CM::Goblin, "Goblin"},
  {CM::Troll, "Troll"},
  {CM::Phoenix, "Phoenix"},
  {CM::Merchant, "Merchant"},
  {CM::Dragon, "Dragon"},
  {CM::Cerberus, "Cerberus"},
  {CM::BabyHound, "Baby Hound"},
  {CM::Witch, "Witch"},
  {CM::Ash, "Ash"}
};

std::map<CM, std::string> potions = {
  {CM::RH, "RH"},
  {CM::BA, "BA"},
  {CM::BD, "BD"},
  {CM::PH, "PH"},
  {CM::WA, "WA"},
  {CM::WD, "WD"}
};

map<int, string> intDir{
  {0, "North"},
  {1, "South"},
  {2, "East"},
  {3, "West"},
  {4, "North West"},
  {5, "North East"},
  {6, "South West"},
  {7, "South East"}
};

map<string, int> strDir {
  {"no", 0},
  {"so", 1},
  {"ea", 2},
  {"we", 3},
  {"nw", 4},
  {"ne", 5},
  {"sw", 6},
  {"se", 7}
};

map<CM, char> cmConversion {
  {CM::RH, 'P'},
  {CM::BA, 'P'},
  {CM::BD, 'P'},
  {CM::PH, 'P'},
  {CM::WA, 'P'},
  {CM::WD, 'P'},
  {CM::NormalGold, 'G'},
  {CM::SmallHorde, 'G'},
  {CM::MerchantHorde, 'G'},
  {CM::DragonHorde, 'G'}, 
  {CM::EmptyTile, ' '},
  {CM::HorizontalWall, '-'},
  {CM::VerticalWall, '|'},
  {CM::Door, '+'},
  {CM::Bridge, '#'},
  {CM::Staircase, '\\'},
  {CM::Werewolf, 'W'},
  {CM::Vampire, 'V'},
  {CM::Goblin, 'N'},
  {CM::Troll, 'T'},
  {CM::Phoenix, 'X'},
  {CM::Merchant, 'M'},
  {CM::Dragon, 'D'},
  {CM::Cerberus, 'C'},
  {CM::BabyHound, 'B'},
  {CM::Witch, 'H'},
  {CM::Ash, 'A'},
  {CM::PC, '@'},
  {CM::ActiveTile, '.'}
};

map<char, CM> charToCmConversion {
  {'0', CM::RH},
  {'1', CM::BA},
  {'2', CM::BD},
  {'3', CM::PH},
  {'4', CM::WA},
  {'5', CM::WD},
  {'6', CM::NormalGold},
  {'7', CM::SmallHorde},
  {'8', CM::MerchantHorde},
  {'9', CM::DragonHorde}, 
  {' ', CM::EmptyTile},
  {'-', CM::HorizontalWall},
  {'|', CM::VerticalWall},
  {'+', CM::Door},
  {'#', CM::Bridge},
  {'\\', CM::Staircase},
  {'W', CM::Werewolf},
  {'V', CM::Vampire},
  {'N', CM::Goblin},
  {'T', CM::Troll},
  {'X', CM::Phoenix},
  {'M', CM::Merchant},
  {'D', CM::Dragon},
  {'C', CM::Cerberus},
  {'B', CM::BabyHound},
  {'H', CM::Witch},
  {'A', CM::Ash},
  {'@', CM::PC},
  {'.', CM::ActiveTile}
};
