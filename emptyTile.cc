#include "emptyTile.h"

EmptyTile::EmptyTile(int x, int y): Tile{x,y} { }

CM EmptyTile::getType() const {
  return CM::EmptyTile; // Return code indicating that the tile is empty
}
