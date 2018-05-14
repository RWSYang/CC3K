#ifndef __GOLD_H__
#define __GOLD_H__

#include "item.h"

class Gold: public Item {
  int value;
  public:
    Gold(int amount);
    virtual ~Gold() = 0;
    int getValue() const ;
};

#endif
