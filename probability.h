#ifndef __PROBABILITY_H__
#define __PROBABILITY_H__
#include <vector>
#include <memory>
#include "charactersMapping.h"

class Item;
class Base;

class Probability {
  std::vector<CM> probPot;
  std::vector<CM> probGold;
  std::vector<CM> probEnemy;
  bool bonus;
  public:
    Probability(bool bonus);
    ~Probability() = default;
    std::shared_ptr<Item> randomPot(int n);
    std::shared_ptr<Item> randomGold(int n);
    std::shared_ptr<Base> randomEnemy(int n);
};

#endif
