#include"poison.h"
#include "player.h"

using namespace std;

bool Poison::hidden = true;

Poison::Poison() {}
Poison::~Poison() {
  hidden = true;
}

CM Poison::getType() const {
  return CM::PH;
}

void Poison::update(Player *p) {
  int temp = p->getHP();
  if(p->getRace() == "Elf") {
    int max = p->getMaxHP();
    if(temp + effect >= max) {
      temp = max;
    } else {
      temp += effect;
    }
  } else {
    if(temp - effect <= 0){
      temp = 0;
    } else { 
      temp -= effect;
    }
  }
  p->setHP(temp);
  hidden = false;
}

bool Poison::getHidden() const {
  return hidden;
}
