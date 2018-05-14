#ifndef __ELF_H__
#define __ELF_H__
#include"player.h"

class Elf : public Player{
  public:
  int attack(Base &e) override;
  void useItem(Item &item) override;
  void updateGold(float) override;
  Elf();
  ~Elf()= default;
};



#endif
