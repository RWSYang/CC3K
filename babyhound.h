#ifndef __BABYHOUND_H__
#define __BABYHOUND_H__

#include "enemy.h"

class BabyHound: public Enemy {
  public:
  BabyHound();
  ~BabyHound()=default;
  int attack(Base &p) override;
  CM getType() const override;
};

#endif
