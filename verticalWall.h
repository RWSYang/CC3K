#ifndef __VERTICALWALL_H__
#define __VERTICALWALL_H__

#include "tile.h"

class VerticalWall: public Tile {
  public:
    VerticalWall(int x, int y);
    ~VerticalWall() = default;
    CM getType() const override;
};

#endif
