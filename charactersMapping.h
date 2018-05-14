#ifndef __CHARACTERSMAPPING_H__
#define __CHARACTERSMAPPING_H__

enum struct CharactersMapping { RH = 0, BA, BD, PH, WA,
  WD, NormalGold, SmallHorde, MerchantHorde,
  DragonHorde, EmptyTile, HorizontalWall, VerticalWall,
  Door, Bridge, Staircase, Werewolf,
  Vampire, Goblin, Troll, Phoenix,
  Merchant, Dragon, PC, ActiveTile, Witch, BabyHound, Cerberus, Ash,
  Potion, Treasure, Enemy, Item};

typedef CharactersMapping CM;

inline bool operator==(CM left, CM right) {
  if (static_cast<int>(left) == static_cast<int>(right)) return true;
  switch(left) {
    case CM::RH: case CM::BA: case CM::BD:
    case CM::PH: case CM::WA: case CM::WD:
      return static_cast<int>(right) == static_cast<int>(CM::Potion);
    case CM::NormalGold: case CM::SmallHorde:
    case CM::MerchantHorde: case CM::DragonHorde:
      return static_cast<int>(right) == static_cast<int>(CM::Treasure);
    case CM::Werewolf: case CM::Vampire: case CM::Goblin:
    case CM::Troll: case CM::Phoenix: case CM::Merchant:
    case CM::Dragon: case CM::Witch: case CM::BabyHound:
    case CM::Cerberus:
      return static_cast<int>(right) == static_cast<int>(CM::Enemy);
    default:
      break;
  }
  return false;
}
#endif
