#include "gold.h"
#include "player.h"

Gold::Gold(int amount): value{amount}{ }

Gold::~Gold() { }

int Gold::getValue() const {
  return value;
}
