#ifndef __TROLL_H__
#define __TROLL_H__

#include"enemy.h"

class Troll: public Enemy{
  public:
  Troll();
  ~Troll()=default;
  int attack(Base &p);
  CM getType() const override;
  // Bonus method
  void regen();
};

#endif
