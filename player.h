#ifndef __PLAYER_H__
#define __PLAYER_H__
#include<string>
#include "base.h"

class Player: public Base {
  float gold = 0;
  float stolen=0;
public:
  Player(int health, int attack, int defense, std::string);
  virtual ~Player() =default;
  CM getType() const override;
  float getGold() const;
  int poisonDamage();
  virtual void updateGold(float gold)=0;
  virtual void useItem(Item &item)=0;
};



#endif
