#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "enemy.h"

class Goblin: public Enemy{
  bool hostile;
  float stolen;
  bool bonus;
  public:
  Goblin(bool);
  ~Goblin();
  bool getHostile() const override;
  int attack(Base &p)override; 
  CM getType() const override;
  // Bonus methods
  float getStolen();
  void stealGold(Player *);
};

#endif
