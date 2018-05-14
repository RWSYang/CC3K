#ifndef __HORIZONTALWALL_H__
#define __HORIZONTALWALL_H__

#include "tile.h"

class HorizontalWall: public Tile {
  public:
    HorizontalWall(int x, int y);
    ~HorizontalWall() = default;
    CM getType() const override;
};

#endif
