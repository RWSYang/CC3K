#ifndef __WOUNDDEF_H__
#define __WOUNDDEF_H__
#include"potion.h"

class WoundDEF : public Potion {
  static bool hidden;
  const int effect = 5;
  public:
  WoundDEF();
  ~WoundDEF();
  CM getType() const override;
  void update(Player *p)override;
  bool getHidden() const override;
};

#endif
