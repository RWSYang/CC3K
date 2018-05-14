#include "bridge.h"
#include <utility>
#include "base.h"
using namespace std;

Bridge::Bridge(int x, int y): Tile{x,y}, pc{nullptr} { }

void Bridge::attachCharacter(Base &pc) {
  this->pc = &pc;
  pair<int, int> coord = getCoordinates();
  this->pc->setCoordinates(coord.first, coord.second);
  notifyObservers();
}

void Bridge::detachCharacter() {
  this->pc = nullptr;
  notifyObservers();
}

CM Bridge::getType() const {
  if (pc != nullptr) return pc->getType();
  return CM::Bridge;
}
