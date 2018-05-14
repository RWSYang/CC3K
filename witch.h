#ifndef __WITCH_H__
#define __WITCH_H__
#include"enemy.h"
class Witch: public Enemy{
  public:
  Witch();
  ~Witch() = default;
  int attack(Base &p) override;
  CM getType() const override;
};

#endif
