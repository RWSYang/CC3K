#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class Human : public Player{
  public:
   Human();
   ~Human() = default;
   int attack(Base &e) override;
   void useItem(Item &item) override;
   void updateGold(float) override;
};

#endif
