#ifndef __POISON_H__
#define __POISON_H__
#include "potion.h"

class Poison: public Potion{
  static bool hidden;
  const int effect = 10;
  public:
  Poison();
  ~Poison();
  CM getType() const override;
  void update(Player *p) override;
  bool getHidden() const override;
};


#endif
