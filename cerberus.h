#ifndef __CERBERUS_H__
#define __CERBERUS_H__

#include "enemy.h"

class Cerberus: public Enemy {
  public:
  Cerberus();
  ~Cerberus()=default;
  int attack(Base &p) override;
  CM getType() const override;
};

#endif
