#ifndef __EMPTYTILE_H__
#define __EMPTYTILE_H__
#include "tile.h"

class EmptyTile: public Tile {
  public:
    EmptyTile(int x, int y);
    ~EmptyTile() = default;
    CM getType() const  override;
};

#endif
