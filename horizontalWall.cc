#include "horizontalWall.h"

HorizontalWall::HorizontalWall(int x, int y): Tile{x,y} { }

CM HorizontalWall::getType() const {
  return CM::HorizontalWall;
}
