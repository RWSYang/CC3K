#include"dragon.h"
#include<cmath>
using namespace std;
Dragon::Dragon(): Enemy(150, 20, 20, "Dragon") {}

CM Dragon::getType() const {
  return CM::Dragon;
}

int Dragon::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point=p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  return damage;
}

pair<int, int> Dragon::getHordePosition() {
  return hordePosition;
}

void Dragon::setHordePosition(pair<int, int> hordePos) {
  hordePosition = hordePos;
}
