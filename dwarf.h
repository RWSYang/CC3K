#ifndef __DWARF_H__
#define __DWARF_H__
#include "player.h"

class Dwarf: public Player {
  public:
  void useItem(Item &item) override;
  int attack(Base &e) override;
  void updateGold(float) override;
  Dwarf();
  ~Dwarf() = default;
};


#endif
