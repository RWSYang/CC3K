#ifndef __DOOR_H__
#define __DOOR_H__

#include "tile.h"
class Base;

class Door: public Tile {
  public:
    Door(int x, int y);
    ~Door() = default;
    void attachCharacter(Base &pc);
    void detachCharacter();
    CM getType() const override;
  private:
    Base *pc;
};

#endif
