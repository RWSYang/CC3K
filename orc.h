#ifndef __ORC_H__
#define __ORC_H__

#include"player.h"

class Orc: public Player{
  public:
  Orc();
  ~Orc()=default;
  int attack(Base &e) override;
  void useItem(Item &item) override;
  void updateGold(float) override;
};

#endif
