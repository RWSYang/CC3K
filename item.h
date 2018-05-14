#ifndef __ITEM_H__
#define __ITEM_H__
#include "charactersMapping.h"
class Player;

class Item {
  public:
    Item() = default;
    virtual ~Item() = default;
    virtual void update(Player *pc) = 0;
    virtual CM getType() const =0;
};

#endif
