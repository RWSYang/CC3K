#include"elf.h"
#include"item.h"
#include<cmath>

using namespace std;

Elf::Elf(): Player(140, 30, 10, "Elf") {}

void Elf::useItem(Item &item) {
  item.update(this);
}


int Elf::attack(Base &e){
  int attack_point=this->getATK();
  int defense_point=e.getDEF();
  int damage = ceil(((100.0/(100.0+defense_point)))*attack_point);
  return damage;
}

void Elf::updateGold(float value) {
  Player::updateGold(value);
}
