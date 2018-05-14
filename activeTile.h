#ifndef __ACTIVETILE_H__
#define __ACTIVETILE_H__
#include <vector>
#include "tile.h"

class Item;
class Base;

class ActiveTile: public Tile {
  Base *bc;
  Item *item;
  public:
    ActiveTile(int x, int y);
    ~ActiveTile() = default;
    void attachCharacter(Base &bc);
    void attachItem(Item &item);
    void detachCharacter();
    void detachItem();
    bool hasPlayer() const;
    bool hasItem() const;
    CM getType() const override;
    Base &getCharacter() const;
    Item &getItem() const;
};

#endif
