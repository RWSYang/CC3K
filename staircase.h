#ifndef __STAIRCASE_H__
#define __STAIRCASE_H__

#include "tile.h"

class Staircase: public Tile {
  public:
    Staircase(int x, int y);
    ~Staircase() = default;
    CM getType() const override;
};

#endif
