#include"witch.h"
#include<cmath>
using namespace std;

Witch::Witch() : Enemy{25, 15, 5, "Witch"} {}

CM Witch::getType() const {
  return CM::Witch;
}

int Witch::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point = p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  p.setPoison(3);
  return damage;
}
