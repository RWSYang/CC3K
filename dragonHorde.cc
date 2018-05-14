#include "player.h"
#include "dragonHorde.h"

DragonH::DragonH(): Gold{6}, available{false} { }

bool DragonH::getAvailable() const {
  return available;
}

void DragonH::changeAvailability() {
  available = true;
}

CM DragonH::getType() const {
  return CM::DragonHorde;
}

void DragonH::update(Player *pc) {
  if (getAvailable()) {
    int gold = getValue();
    pc->updateGold(gold);
  }
}
