#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "base.h"
#include <string>

class Player;

class Enemy: public Base{
public:
  Enemy(int, int, int, std::string);
  virtual ~Enemy() = 0;
	bool checkRadius(Player &p);
  bool isAlive();
  virtual bool getHostile() const;
  virtual void setHostile();
};

#endif
