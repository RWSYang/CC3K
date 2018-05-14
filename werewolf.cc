#include"werewolf.h"
#include<cmath>
using namespace std;

Werewolf::Werewolf(): Enemy(120, 30, 5, "Werewolf") {}

CM Werewolf::getType() const {
  return CM::Werewolf;
}


int Werewolf::attack(Base &p) {
  int attack_point=this->getATK();
  int defense_point=p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  return damage;
}
