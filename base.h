#ifndef __BASE_CHARACTER_H__
#define __BASE_CHARACTER_H__
#include <utility>
#include <string>
#include "charactersMapping.h"
class Item;

class Base {
  int HP;
  int Max_HP;
  int DEF;
  int ATK;
  int TMP_ATK;
  int TMP_DEF;
  int Pos_X;
  int Pos_Y;
  std::string race;
  int poison;
  public:
  Base(int hp, int atk, int def, std::string="");
  virtual ~Base();
  int getMaxHP() const;
  int getHP() const;
  void setHP(int hp);
  int getATK() const;
  void setATK(int atk);
  int getDEF() const;
  void setDEF(int def);
  void resetAtkDef();
  std::pair<int, int> getCoordinates();
  void setCoordinates(int, int);
  virtual int attack(Base &p) = 0;
  virtual CM getType() const = 0;
  std::string getRace() const;
  //bonus methods
  int getPoison();
  void setPoison(int);
};
#endif
