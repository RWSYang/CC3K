#ifndef __BOOSTATK_H__
#define __BOOSTATK_H__
#include "potion.h"
#include "player.h"
class Player;

class BoostATK: public Potion{
  static bool hidden;
  const int effect = 5;
  public:
  BoostATK();
  ~BoostATK();
  CM getType() const override;
  void update(Player *p) override;
  bool getHidden() const override;
};

#endif
