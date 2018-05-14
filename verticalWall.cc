#include "verticalWall.h"

VerticalWall::VerticalWall(int x, int y): Tile{x,y} { }

CM VerticalWall::getType() const {
  return CM::VerticalWall;
}
