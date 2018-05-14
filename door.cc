#include "door.h"
#include <utility>
#include "base.h"
using namespace std;

Door::Door(int x, int y): Tile{x,y}, pc{nullptr} { }

void Door::attachCharacter(Base &pc) {
  this->pc = &pc;
  pair<int, int> coord = getCoordinates();
  this->pc->setCoordinates(coord.first, coord.second);
  notifyObservers();
}

void Door::detachCharacter() {
  this->pc = nullptr;
  notifyObservers();
}

CM Door::getType() const {
  if (pc != nullptr) return pc->getType();
  return CM::Door;
}
