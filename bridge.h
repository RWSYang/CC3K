#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "tile.h"
class Base;

class Bridge: public Tile {
    Base *pc;
  public:
    Bridge(int x, int y);
    ~Bridge() = default;
    void attachCharacter(Base &pc);
    void detachCharacter();
    CM getType() const override;
};

#endif
