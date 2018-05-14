#ifndef __BOOSTDEF_H__
#define __BOOSTDEF_H__
#include"potion.h"

class BoostDEF:public Potion{
  static bool hidden;
  const int effect = 5;
  public:
  BoostDEF();
  ~BoostDEF();
  CM getType() const override;
  void update(Player *p)override;
  bool getHidden() const override;
};

#endif
