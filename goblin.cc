#include "goblin.h"
#include "player.h"
#include <cmath>

using namespace std;
Goblin::Goblin(bool bonus) :Enemy(70, 5, 10, "Goblin"), hostile{true}, bonus{bonus} {}

Goblin::~Goblin() { }

CM Goblin::getType() const {
  return CM::Goblin;
}

int Goblin::attack(Base &p) {
  int attack_point = this->getATK();
  int defense_point = p.getDEF();
  int damage = ceil((100.0/(100.0 + defense_point)) * attack_point);
  if(bonus) {
   Base *base = &p;
   Player *pc = dynamic_cast<Player*>(base);
   stealGold(pc);
  }
  return damage;
}

bool Goblin::getHostile() const {
  return hostile;
}

void Goblin::stealGold(Player *p) {
  float steal = ceil(p->getGold() * .1);
  stolen = steal;
  steal *=-1;
  p->updateGold(steal);
  hostile = false;
}
float Goblin::getStolen() {
  return stolen;
}
