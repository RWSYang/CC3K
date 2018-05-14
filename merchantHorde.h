#ifndef __MERCHANTHORDE_H__
#define __MERCHANTHORDE_H__

#include"gold.h"

class MerchantH: public Gold {
  public:
    MerchantH();
    ~MerchantH() = default;
    CM getType() const override;
    void update(Player *pc) override;
};

#endif
