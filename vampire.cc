#include"vampire.h"
#include<cmath>
using namespace std;

Vampire::Vampire(bool bonus): Enemy(50, 25, 25, "Vampire"), bonus{bonus} {}

CM Vampire::getType() const {
  return CM::Vampire;
}


int Vampire::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point = p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point))) * attack_point; 
  if(bonus){
    // for every damage, vampire consumes 10% of the blood
    int blood = ceil(damage * 0.1);
    this->setHP(this->getHP() + blood);
  }
  return damage;
}
