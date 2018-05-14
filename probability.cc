#include "probability.h"
#include "restoreH.h"
#include "boostAtk.h"
#include "boostDef.h"
#include "poison.h"
#include "woundAtk.h"
#include "woundDef.h"
#include "normalHorde.h"
#include "smallHorde.h"
#include "merchantHorde.h"
#include "dragonHorde.h"
#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "phoenix.h"
#include "troll.h"
#include "merchant.h"
#include "witch.h"
#include "cerberus.h"

using namespace std;

Probability::Probability(bool bonus): bonus{bonus} {
  // no bonus implementation affecting potion and gold spawns
  probPot = vector<CM>{CM::RH, CM::BA, CM::BD, CM::PH, CM::WA, CM::WD};
  probGold = vector<CM>{CM::NormalGold, CM::NormalGold, CM::NormalGold, CM::NormalGold, 
    CM::NormalGold, CM::SmallHorde, CM::SmallHorde, CM::DragonHorde}; 
  if(!bonus) {
    probEnemy = vector<CM>{CM::Werewolf, CM::Werewolf, CM::Werewolf, CM::Werewolf, 
      CM::Vampire, CM::Vampire, CM::Vampire, CM::Goblin, CM::Goblin, CM::Goblin, CM::Goblin, 
      CM::Goblin, CM::Troll, CM::Troll, CM::Phoenix, CM::Phoenix, CM::Merchant, CM::Merchant};
  } else {
    probEnemy = vector<CM>{CM::Werewolf, CM::Werewolf, CM::Witch, CM::Witch, 
      CM::Vampire, CM::Vampire, CM::Vampire, CM::Goblin, CM::Goblin, CM::Cerberus, CM::Cerberus, 
      CM::Cerberus, CM::Troll, CM::Troll, CM::Phoenix, CM::Phoenix, CM::Merchant, CM::Merchant};
  }
}

shared_ptr<Item> Probability::randomPot(int n){
  CM rand = probPot[n];
  shared_ptr<Item> pot;
  switch(rand){
    case CM::RH:
      pot = make_shared<RestoreH>();
      break;
    case CM::BA:
      pot = make_shared<BoostATK>();
      break;
    case CM::BD:
      pot = make_shared<BoostDEF>();
      break;
    case CM::PH:
      pot = make_shared<Poison>();
      break;
    case CM::WA:
      pot = make_shared<WoundATK>();
      break;
    case CM::WD:
      pot = make_shared<WoundDEF>();
      break;
    default:
      break;
  }
  return pot;
}

shared_ptr<Item> Probability::randomGold(int n){
  CM rand = probGold[n];
  shared_ptr<Item> gold;
  switch (rand){
    case CM::NormalGold:
      gold = make_shared<NormalH>();
      break;
    case CM::SmallHorde:
      gold = make_shared<SmallH>();
      break;
    case CM::DragonHorde:
      gold = make_shared<DragonH>();
      break;
    default:
      break;
  }
  return gold;
}

shared_ptr<Base> Probability::randomEnemy(int n){
  CM rand = probEnemy[n];
  shared_ptr<Base> enemy;
  switch(rand){
    case CM::Werewolf:
      enemy = make_shared<Werewolf>();
      break;
    case CM::Vampire: 
      enemy = make_shared<Vampire>(bonus);
      break;
    case CM::Goblin:
      enemy = make_shared<Goblin>(bonus);
      break;
    // bonus class enemy
    case CM::Cerberus:
      enemy = make_shared<Cerberus>();
      break;
    // bonus class enemy
    case CM::Witch:
      enemy = make_shared<Witch>();
      break;
    case CM::Troll:
      enemy = make_shared<Troll>();
      break;
    case CM::Phoenix:
      enemy = make_shared<Phoenix>();
      break;
    case CM::Merchant:
      enemy = make_shared<Merchant>();
      break;
    default:
      break;
  }
  return enemy;
}
