#include"boostAtk.h"
#include "player.h"

using namespace std;

bool BoostATK::hidden = true;

BoostATK::BoostATK() {}
BoostATK::~BoostATK() {
  hidden = true;
}
CM BoostATK::getType() const {
  return CM::BA;
}

void BoostATK::update(Player *p) {
  int temp = p->getATK();
  temp += effect;
  p->setATK(temp);
  hidden = false;
}

bool BoostATK::getHidden() const {
  return hidden;
}
