#include "boostDef.h"
#include "player.h"

using namespace std;

bool BoostDEF::hidden = true;

BoostDEF::BoostDEF() {}
BoostDEF::~BoostDEF() {
  hidden = true;
}
CM BoostDEF::getType() const {
  return CM::BD;
}

void BoostDEF::update(Player *p) {
  int temp = p->getDEF();
  temp += effect;
  p->setDEF(temp);
  hidden = false;
}

bool BoostDEF::getHidden() const {
  return hidden;
}
