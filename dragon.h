#ifndef __DRAGON_H__
#define __DRAGON_H__

#include"enemy.h"

class Dragon: public Enemy{
  bool hostile;
  std::pair<int, int> hordePosition;
  public:
  Dragon();
  ~Dragon()=default;
  int attack(Base &p) override;
  CM getType() const override;
  std::pair<int, int> getHordePosition();
  void setHordePosition(std::pair<int, int> hordePos);
};

#endif
