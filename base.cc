#include"base.h"
using namespace std;

Base::Base(int health, int attack, int defense, std::string type): 
  HP{health}, Max_HP{health}, DEF{defense}, ATK{attack}, 
  TMP_ATK{attack}, TMP_DEF{defense}, race{type}, poison{0} {}

Base::~Base() {}

int Base::getHP() const{
  return HP;
}
int Base::getPoison() {
  return poison;
}
void Base::setPoison(int turn) {
  poison= turn;
}
void Base::setHP(int health){
  HP = health;
}

int Base::getATK() const{
  return TMP_ATK;
}

int Base::getDEF() const {
  return TMP_DEF;
}

void Base::setATK(int attack) {
  TMP_ATK=attack;
}

void Base::setDEF(int defense) {
  TMP_DEF=defense;
}

void Base::resetAtkDef(){
  TMP_ATK = ATK;
  TMP_DEF = DEF;
}

std::pair<int, int> Base::getCoordinates(){
  std::pair <int, int> coord (Pos_X, Pos_Y);
  return coord;
}

void Base::setCoordinates(int x, int y) {
  Pos_X= x;
  Pos_Y= y;
}

std::string Base::getRace() const{
  return race;
}

int Base::getMaxHP() const{
  return Max_HP;
}
