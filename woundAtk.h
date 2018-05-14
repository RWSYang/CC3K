#ifndef __WOUNDATK_H__
#define __WOUNDATK_H__
#include"potion.h"

class WoundATK : public Potion{
  static bool hidden;
  const int effect = 5;
  public:
  WoundATK();
  ~WoundATK();
  CM getType() const override;
  void update(Player *p)override;
  bool getHidden() const override;
};

#endif
