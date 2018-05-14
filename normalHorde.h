#ifndef __NORMALHOARD_H__
#define __NORMALHOARD_H__

#include"gold.h"

class NormalH: public Gold {
  public:
    NormalH();
    ~NormalH()=default;
    CM getType() const override;
    void update(Player *pc) override;
};

#endif
