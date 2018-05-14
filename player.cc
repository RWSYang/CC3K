#include<iostream>
#include"player.h"
using namespace std;

Player::Player(int health, int attack, int defense, std::string type) : Base(health, attack, defense, type) {}

float Player::getGold() const{
  return gold;
}

void Player::updateGold(float gold){
  this->gold += gold;
  if(this->gold <0) {
    this->gold = 0;
  }
}

int Player::poisonDamage() {
  int poison = this->getPoison();
  if(poison > 0) {
    int hp = this->getHP();
    hp -=5;
    this->setHP(hp);
    --poison;
    this->setPoison(poison);
  }
  return poison;
}

CM Player::getType() const {
  return CM::PC;
}

