#include"smallHorde.h"
#include"player.h"
SmallH::SmallH(): Gold{2} { }

CM SmallH::getType() const {
  return CM::SmallHorde;
}

void SmallH::update(Player *pc) {
  int gold = getValue();
  pc->updateGold(gold);
}
