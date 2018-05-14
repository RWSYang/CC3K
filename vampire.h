#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__

#include"enemy.h"

class Vampire: public Enemy{
  bool bonus;
  public:
  Vampire(bool bonus);
  ~Vampire()=default;
  int attack(Base &p)override;
  CM getType() const override;
};
#endif
