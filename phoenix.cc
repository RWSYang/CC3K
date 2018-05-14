#include"phoenix.h"
#include<cmath>

using namespace std;

Phoenix::Phoenix(): Enemy{50, 35, 20, "Phoenix"}, hostile{true}, isAsh{false} {}

int Phoenix::attack(Base &p) {
  int attack_point=this->getATK();
  int defense_point=p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  return damage;
}

bool Phoenix::getHostile() const {
  return hostile;
}

void Phoenix::died(){
  isAsh = true;
  hostile = false;
  resurrectCount = 7;
}

void Phoenix::alive(){
  isAsh = false;
  hostile = true;
}

int Phoenix::getCount(){
  return resurrectCount;
}

void Phoenix::setCount(int c){
  resurrectCount = c;
}

CM Phoenix::getType() const {
  if(isAsh){
    return CM::Ash;
  } else {
    return CM::Phoenix;
  }
}
