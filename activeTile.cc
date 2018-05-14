#include "activeTile.h"
#include "item.h"
#include "base.h"
#include <utility>
using namespace std;

ActiveTile::ActiveTile(int x, int y): Tile{x,y}, bc{nullptr}, item{nullptr} {}

void ActiveTile::attachCharacter(Base &base) {
#if DEBUG_LEVEL > 0
  if (item != nullptr) cerr << "Trying to add a character to a tile that has an item\n";
#endif
  bc = &base;
  pair<int, int> coord = getCoordinates();
  bc->setCoordinates(coord.first, coord.second);
  notifyObservers();
}

void ActiveTile::attachItem(Item &item) {
#if DEBUG_LEVEL > 0
  if (bc != nullptr) cerr << "Trying to add an item to a tile that has a character\n";
#endif
  this->item = &item;
  notifyObservers();
}

void ActiveTile::detachCharacter() {
  bc = nullptr;
  notifyObservers();
}

void ActiveTile::detachItem() {
  item = nullptr;
  notifyObservers();
}

bool ActiveTile::hasPlayer() const {
  return bc != nullptr;
}

bool ActiveTile::hasItem() const {
  return item != nullptr;
}

CM ActiveTile::getType() const{
  if (bc != nullptr) return bc->getType();
  if (item != nullptr) return item->getType();
  return CM::ActiveTile; // Returns code indicating that the Tile is empty
}

Base &ActiveTile::getCharacter() const {
  return *bc;
}

Item &ActiveTile::getItem() const {
  return *item;
}
