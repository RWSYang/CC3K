#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__

#include"enemy.h"

class Werewolf: public Enemy{
  public:
  Werewolf();
  ~Werewolf()=default;
  int attack(Base &p)override;
  CM getType() const override;
};

#endif
