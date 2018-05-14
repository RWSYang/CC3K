#include"player.h"
#include"item.h"
#include<cmath>
#include "orc.h"

using namespace std;

Orc::Orc() : Player(180, 30, 25, "Orc") {} 

void Orc::useItem(Item &item) {
    item.update(this);
}

int Orc::attack(Base &e) {
  int attack_point=this->getATK();
  int defense_point=e.getDEF();
  int damage = ceil(((100.0/(100.0+defense_point)))*attack_point);
  return damage;
}

void Orc::updateGold(float value) {
  float gold = value * .5;
  Player::updateGold(gold);
}
