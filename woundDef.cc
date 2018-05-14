#include"woundDef.h"
#include "player.h"

using namespace std;

bool WoundDEF::hidden = true;
WoundDEF::WoundDEF() {}

WoundDEF::~WoundDEF() {
  hidden = true;
}
CM WoundDEF::getType() const {
  return CM::WD;
}

void WoundDEF::update(Player *p) {
  int temp = p->getDEF();
  if(p->getRace() == "Elf") {
    temp += effect;
  } else {
    if(temp - effect <= 0){
      temp = 0;
    } else {
      temp -= effect;
    }
  }
  p->setDEF(temp);
  hidden = false;
}

bool WoundDEF::getHidden() const {
  return hidden;
}
