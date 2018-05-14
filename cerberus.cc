#include "cerberus.h"
#include <cmath>
using namespace std;

Cerberus::Cerberus(): Enemy(60, 30, 30, "Cerberus") {}

CM Cerberus::getType() const {
  return CM::Cerberus;
}

int Cerberus::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point = p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  return damage;
}
