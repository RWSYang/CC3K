#ifndef __SMALLHOARD_H__
#define __SMALLHOARD_H__

#include"gold.h"

class SmallH: public Gold {
  public:
    SmallH();
    ~SmallH() = default;
    CM getType() const override;
    void update(Player *pc) override;
};
#endif
