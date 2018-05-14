#include"woundAtk.h"
#include "player.h"

using namespace std;

bool WoundATK::hidden = true;
WoundATK::WoundATK() {}

WoundATK::~WoundATK() {
  hidden = true;
}
CM WoundATK::getType() const{
  return CM::WA;
}

void WoundATK::update(Player *p) {
  int temp = p->getATK();
  if(p->getRace() == "Elf") {
    temp += effect;
  } else {
    if(temp - effect <= 0){
      temp = 0;
    } else {
      temp -= effect;
    }
  }
  hidden = false;
  p->setATK(temp);
}

bool WoundATK::getHidden() const {
  return hidden;
}
