#ifndef __RESTOREH_H__
#define __RESTOREH_H__
#include"potion.h"

class Player;

class RestoreH : public Potion{
  static bool hidden; 
  const int effect = 10;
  public:
  RestoreH();
  ~RestoreH();
  CM getType() const override;
  void update(Player *p)override;
  bool getHidden() const override;
};

#endif
