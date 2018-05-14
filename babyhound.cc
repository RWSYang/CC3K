#include "babyhound.h"
#include <cmath>
using namespace std;

BabyHound::BabyHound(): Enemy(20,10,10, "BabyHound") {}

CM BabyHound::getType() const {
  return CM::BabyHound;
}

int BabyHound::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point = p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  return damage;
}
