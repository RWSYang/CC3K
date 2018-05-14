#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"

class Potion: public Item {
  public:
    Potion();
    virtual ~Potion();
    virtual bool getHidden() const =0;
};

#endif
