#include "tile.h"
#include "observer.h"

using namespace std;

Tile::Tile(int x, int y): coordinate{x,y} { }

pair<int,int> Tile::getCoordinates() const {
  return coordinate;
}

void Tile::attach(Observer &ob) {
  observers.emplace_back(&ob);
}

void Tile::notifyObservers() {
  for (auto ob : observers) ob->notify(*this);
}
