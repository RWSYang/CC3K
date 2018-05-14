#ifndef __CODECONVERSION_H__
#define __CODECONVERSION_H__

#include <map>
#include <string>
#include "charactersMapping.h"

extern std::map<std::string, std::string> races;

extern std::map<std::string, int> racesInt;

extern std::map<int, std::string> intRaces;

extern std::map<std::string, std::string> directions;

extern std::map<CM, std::string> enemies;

extern std::map<CM, std::string> potions;

extern std::map<int, std::string> intDir;

extern std::map<std::string, int> strDir;

extern std::map<CM, char> cmConversion;

extern std::map<char, CM> charToCmConversion;
#endif
