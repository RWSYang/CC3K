#include <cmath>
#include"item.h"
#include "human.h"
using namespace std;


Human::Human(): Player(140, 20, 20, "Human") {}


void Human::useItem(Item &item) {
  item.update(this);
}

int Human::attack(Base &e) {
  int attack_point = this->getATK();
  int defense_point=e.getDEF();
  int damage= ceil((100.0/(100.0+defense_point)) * attack_point);
  return damage;
}

void Human::updateGold(float value) {
  Player::updateGold(value);
}
