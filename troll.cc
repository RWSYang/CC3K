using namespace std;
#include"troll.h"
#include<cmath>

Troll::Troll() : Enemy{120, 25, 15, "Troll"} {}

int Troll::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point=p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  return damage;
}

CM Troll::getType() const {
  return CM::Troll;
}

void Troll::regen() {
  int health = this->getHP();
  int max = this->getMaxHP();
  if(health + 5 >= max) {
    health = max;
  } else {
    health +=5;
  }
  this->setHP(health);
}
