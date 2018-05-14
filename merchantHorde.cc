#include"merchantHorde.h"
#include"player.h"

MerchantH::MerchantH(): Gold{4} { }

CM MerchantH::getType() const {
  return CM::MerchantHorde;
}

void MerchantH::update(Player *pc) {
  int gold = getValue();
  pc->updateGold(gold);
}
