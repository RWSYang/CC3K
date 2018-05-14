#include"merchant.h"
#include<cmath>
using namespace std;
Merchant::Merchant() :Enemy(30, 70, 5, "Merchant") {}
bool Merchant::hostile = false;

Merchant::~Merchant() {
  hostile = false;
}

int Merchant::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point = p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  if(!getHostile()){
    damage = -1; //if not hostile, returns no damage
  }
  return damage;
}

CM Merchant::getType() const {
  return CM::Merchant;
}

void Merchant::setHostile() {
  hostile = true;
}

bool Merchant::getHostile() const {
  return hostile;
}

