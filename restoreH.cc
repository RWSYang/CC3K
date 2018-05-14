#include"restoreH.h"
#include "player.h"

using namespace std;

bool RestoreH::hidden = true;

RestoreH::RestoreH() {}
RestoreH::~RestoreH() {
  hidden = true;
}

CM RestoreH::getType() const {
  return CM::RH;
}

void RestoreH::update(Player *p) {
  int max = p->getMaxHP();
  int temp = p->getHP();
  p->setPoison(0);
  if(temp + effect >= max) {
    temp = max;
  } else {
    temp += effect;
  }
  hidden = false;
  p->setHP(temp);
}

bool RestoreH::getHidden() const {
  return hidden;
}
