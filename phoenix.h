#ifndef __PHOENIX_H__
#define __PHOENIX_H__
#include"enemy.h"

class Phoenix : public Enemy{
  bool hostile;
  bool isAsh;
  int resurrectCount;
  public:
  Phoenix();
  ~Phoenix()=default;
  int attack(Base &p)override;
  CM getType()const override;
  bool getHostile() const override;
  // Bonus methods
  int getCount();
  void setCount(int c);
  void died();
  void alive();
};


#endif
