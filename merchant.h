#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include"enemy.h"

class Merchant : public Enemy{
  static bool hostile;
  public:
  Merchant();
  ~Merchant();
  int attack(Base &p)override;
  CM getType() const override;
  void setHostile()override;
  bool getHostile() const override;
};

#endif
