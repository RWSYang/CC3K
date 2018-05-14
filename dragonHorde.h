#ifndef __DRAGONHORDE_H__
#define __DRAGONHORDE_H__

#include "gold.h"

class DragonH : public Gold{
  bool available;
  public:
    DragonH();
    ~DragonH() = default;
    bool getAvailable() const ;
    void changeAvailability();
    CM getType() const override;
    void update(Player *pc) override;
};

#endif
