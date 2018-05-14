#include"dwarf.h"
#include"item.h"
#include<cmath>
using namespace std;

Dwarf::Dwarf() : Player(100, 20, 30, "Dwarf"){}

void Dwarf::useItem(Item &item) {
  item.update(this);
}

int Dwarf::attack(Base &e) {
  int attack_point=this->getATK();
  int defense_point=e.getDEF();
  int damage=ceil(((100.0/(100.0+defense_point))) * attack_point);
  return damage;
}

void Dwarf::updateGold(float value) {
  Player::updateGold(2 * value);
}
