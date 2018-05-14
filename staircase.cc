#include "staircase.h"

Staircase::Staircase(int x, int y): Tile{x,y} {}

CM Staircase::getType() const {
  return CM::Staircase;
}
