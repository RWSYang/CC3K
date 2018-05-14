#include"normalHorde.h"
#include"player.h"
NormalH::NormalH(): Gold{1} { }

CM NormalH::getType() const {
  return CM::NormalGold;
}

void NormalH::update(Player *pc) {
  int gold = getValue();
  pc->updateGold(gold);
}
