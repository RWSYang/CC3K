#include <algorithm>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include "floor.h"
#include "textdisplay.h"
#include "activeTile.h"
#include "emptyTile.h"
#include "horizontalWall.h"
#include "verticalWall.h"
#include "staircase.h"
#include "door.h"
#include "bridge.h"
#include "gold.h"
#include "item.h"
#include "enemy.h"
#include "dragon.h"
#include "babyhound.h"
#include "potion.h"
#include "defaultMap.h"
#include <queue>
#include "player.h"
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
#include "witch.h"
#include "merchant.h"
#include "cerberus.h"
#include "messagesCode.h"
#include "codeConversion.h"
using namespace std;

bool Floor::flag = false;

Floor::Floor(int floorNum, bool bonus): floorNum{floorNum}, bonus{bonus}, playerInitialPosition{0, 0} {
  if(!flag) {
    srand(time(NULL));
    flag = true;
  }
  p = make_unique<Probability>(bonus);
}
  
Floor::Floor(int floorNum, bool bonus, vector<CM>& vcm): 
  floorNum{floorNum}, bonus{bonus}, charMapFloor{vcm}, playerInitialPosition{0, 0} {
  if(!flag) {
    srand(time(NULL));
    flag = true;
  }
  filePresent = true;
  p = make_unique<Probability>(bonus);
}

Floor::~Floor(){}

void Floor::setPlayer(shared_ptr<Player> p) {
  race = p;
  // Tells a Textdisplay class about Player's information
  sendInfoMessages();
  td->sendMessage(make_tuple(MC::PlayerSpawn, CM::PC, static_cast<float>(floorNum), racesInt[race->getRace()]));
  auto activeTile = static_pointer_cast<ActiveTile>(getTileByPair(playerInitialPosition));
  activeTile->attachCharacter(*static_pointer_cast<Base>(p));
}

void Floor::sendInfoMessages() const {
  string s{race->getRace()};
  int r = racesInt[s];
  td->sendMessage(make_tuple(MC::PlayerRace, CM::PC, 0, r));
  td->sendMessage(make_tuple(MC::PlayerGold, CM::PC, race->getGold(), 0));
  td->sendMessage(make_tuple(MC::CurrentFloor, CM::PC, floorNum, 0));
  td->sendMessage(make_tuple(MC::PlayerHP, CM::PC, race->getHP(), 0));
  td->sendMessage(make_tuple(MC::PlayerATK, CM::PC, race->getATK(), 0));
  td->sendMessage(make_tuple(MC::PlayerDEF, CM::PC, race->getDEF(), 0));
}

void Floor::identifyChambers() {
  int countChambers = 0;
  set<pair<int, int>> visitedTiles;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      pair<int, int> curCoordinate{i, j}; // Current coordinate that is being checked
      if (visitedTiles.count(curCoordinate) == 0)
      {
        visitedTiles.emplace(curCoordinate);
        CM type = tileFloor[i][j]->getType();
        if (type != CM::VerticalWall && type != CM::HorizontalWall &&
            type != CM::EmptyTile && type != CM::Bridge && type != CM::Door){ 
          // These tiles don't belong to a chamber
          vector<pair<int, int>> vFloorChambers;
          tileChamb.emplace_back(vFloorChambers);
          ++countChambers;
          // Does a breadth-first search to find all the ActiveTiles in this chamber
          exploreSurroundings(curCoordinate, visitedTiles, countChambers - 1);
        }
      }
    }
  }
}

void Floor::exploreSurroundings(pair<int, int> coordinate, 
  set<pair<int, int>> &visitedTiles, int chamberNumber) {
  queue<pair<int, int>> tiles;
  tiles.emplace(coordinate);
  // Iterator to be used within the method emplace_hint to the set
  auto hintIterator = visitedTiles.cbegin();
  while (!tiles.empty()) {
    pair<int, int> nextTile = tiles.front();
    tiles.pop();
    int x = nextTile.first;
    int y = nextTile.second;
    tileChamb[chamberNumber].emplace_back(pair<int, int>(x, y));
    // Checks tile on east
    pair<int, int> eastTile{x, y + 1};
    if (visitedTiles.count(eastTile) == 0) {
      if (getTileByPair(eastTile)->getType() == CM::ActiveTile) {
        tiles.emplace(eastTile);
      }
      hintIterator = visitedTiles.emplace_hint(hintIterator, eastTile);
    }
    // Checks tile on south
    pair<int, int> southTile{x + 1, y};
    if (visitedTiles.count(southTile) == 0) {
      if (getTileByPair(southTile)->getType() == CM::ActiveTile) {
        tiles.emplace(southTile);
      }
      hintIterator = visitedTiles.emplace_hint(hintIterator, southTile);
    }
    // Checks tile on west
    pair<int, int> westTile{x, y - 1};
    if (visitedTiles.count(westTile) == 0) {
      if (getTileByPair(westTile)->getType() == CM::ActiveTile) {
        tiles.emplace(westTile);
      }
      hintIterator = visitedTiles.emplace_hint(hintIterator, westTile);
    }
    // Checks tile on north
    pair<int, int> northTile{x - 1, y};
    if (visitedTiles.count(northTile) == 0) { // Not visited yet
      if (getTileByPair(northTile)->getType() == CM::ActiveTile) {
        tiles.emplace(northTile);
      }
      hintIterator = visitedTiles.emplace_hint(hintIterator, northTile);
    }
  }
}

shared_ptr<Tile> Floor::getTileByPair(pair<int, int> p) {
  return tileFloor[p.first][p.second];
}

// Compiles and creates an appropriate type for the given layout
shared_ptr<Tile> Floor::createTile(int x, int y, CM type) {
  shared_ptr<Tile> t;
  shared_ptr<Base> b;
  shared_ptr<Item> i;
  switch (type){
    case CM::EmptyTile: 
      t = make_shared<EmptyTile>(x, y);
      break;
    case CM::HorizontalWall:
      t = make_shared<HorizontalWall>(x, y);
      break;
    case CM::VerticalWall:
      t = make_shared<VerticalWall>(x, y);
      break;
    case CM::Door:
      t = make_shared<Door>(x, y);
      break;
    case CM::Bridge:
      t = make_shared<Bridge>(x, y);
      break;
    case CM::ActiveTile:
      t = make_shared<ActiveTile> (x, y);
      break;
    case CM::Staircase:
      t = make_shared<Staircase> (x, y);
      stairCoord.first = x;
      stairCoord.second = y;
      break;
    case CM::RH:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<RestoreH>();
      break;
    case CM::BA:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<BoostATK>();
      break;
    case CM::BD:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<BoostDEF>();
      break;
    case CM::PH:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<Poison>();
      break;
    case CM::WA:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<WoundATK>();
      break;
    case CM::WD:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<WoundDEF>();
      break;
    case CM::NormalGold:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<NormalH>();
      break;
    case CM::SmallHorde:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<SmallH>();
      break;
    case CM::MerchantHorde:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<MerchantH>();
      break;
    case CM::DragonHorde:
      t = make_shared<ActiveTile> (x, y);
      i = make_shared<DragonH>();
      dragonHordesCoordinate.emplace_back(pair<int, int>{x, y});
      break;
    case CM::Werewolf:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Werewolf>();
      break;
    case CM::Vampire:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Vampire>(bonus);
      break;
    case CM::Goblin:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Goblin>(bonus);
      break;
    case CM::Troll:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Troll>();
      break;
    case CM::Phoenix: case CM::Ash:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Phoenix>();
      break;
    case CM::Merchant:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Merchant>();
      break;
    case CM::Witch:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Witch>();
      break;
    case CM::Dragon:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Dragon>();
      dragonsCoordinate.emplace_back(pair<int, int>{x, y});
      break;
    case CM::Cerberus:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<Cerberus>();
      break;
    case CM::BabyHound:
      t = make_shared<ActiveTile> (x, y);
      b = make_shared<BabyHound>();
    case CM::PC:
      t = make_shared<ActiveTile> (x, y);
      playerInitialPosition = {x, y};
      break;
    default:
      break;
  }
  if (b != nullptr) {
    auto p2 = static_pointer_cast<ActiveTile>(t);
    p2->attachCharacter(*b);
    if (b->getType() != CM::PC) {
      vecEnemies.emplace_back(static_pointer_cast<Enemy>(b));
    }
    t = move(static_pointer_cast<Tile>(p2));
  } else if (i != nullptr) {
    auto p2 = static_pointer_cast<ActiveTile>(t);
    p2->attachItem(*i);
    vecItems.emplace_back(i);
    t = move(static_pointer_cast<Tile>(p2));
  }
  return t;
}

int Floor::randNumGen(int total){
  int randNum = rand() % total;
  return randNum;
}

vector<pair<int,int>> Floor::vectorAround(int x, int y){ 
  vector<pair<int,int>> vp;
  for(int i = x-1; i <= x+1; ++i){
    if(i < 0 || i >= row) continue;
    for(int j = y-1; j <= y+1; ++j){
      if(j < 0 || j >= column || (x == i && y == j)) continue;
      shared_ptr<Tile> t = tileFloor[i][j];
      shared_ptr<ActiveTile> at = dynamic_pointer_cast<ActiveTile>(t);
      if(at == nullptr || at->hasPlayer() || at->hasItem()) continue;
      pair <int,int> coord = make_pair(i,j);
      vp.emplace_back(coord);
    }
  }
  return vp;
}

bool Floor::pcNearItem(int x, int y){
  pair<int,int> pcPos = race->getCoordinates(); 
  for(int i = x-1; i <= x+1; ++i){
    for(int j = y-1; j <= y+1; ++j){
      if(i == pcPos.first && j == pcPos.second){
        return true;
      }
    }
  }
  return false;
}

// Bonus pursuit/flee method
pair<int,int> Floor::pursuePlayer(int x, int y, bool chase){
  pair<int, int> playerPos = race->getCoordinates();
  if(!chase) {
    // Reverses the coordinates of Player wrt to Enemy's coordinate
    if(x > playerPos.first) {
      playerPos.first += (x - playerPos.first) * 2;
    } else {
      playerPos.first -= (playerPos.first - x) * 2;
    }
    if(y > playerPos.second) {
      playerPos.second += (y - playerPos.second) * 2;
    } else {
      playerPos.second -= (playerPos.second - y) * 2;
    }
  }
  vector<pair<int,int>> moves;
  if(abs(playerPos.first - x) > radius || abs(playerPos.second - y) > radius){
    // By returning the original coordinates, we let the enemy move at random
    return pair<int,int>{x,y};
  }
  if(x == playerPos.first){
    if(y < playerPos.second){
      // 5 best moves that the enemy can take in order
      moves.emplace_back(pair<int,int>{x,y+1});
      moves.emplace_back(pair<int,int>{x+1,y+1});
      moves.emplace_back(pair<int,int>{x-1,y+1});
      moves.emplace_back(pair<int,int>{x+1,y});
      moves.emplace_back(pair<int,int>{x-1,y});
    } else {
      moves.emplace_back(pair<int,int>{x,y-1});
      moves.emplace_back(pair<int,int>{x+1,y-1});
      moves.emplace_back(pair<int,int>{x-1,y-1});
      moves.emplace_back(pair<int,int>{x+1,y});
      moves.emplace_back(pair<int,int>{x-1,y});
    }
  } else if (x < playerPos.first){
    if(y < playerPos.second){ 
      moves.emplace_back(pair<int,int>{x+1,y+1});
      moves.emplace_back(pair<int,int>{x,y+1});
      moves.emplace_back(pair<int,int>{x+1,y});
      moves.emplace_back(pair<int,int>{x-1,y+1});
      moves.emplace_back(pair<int,int>{x+1,y-1});
    } else if(y > playerPos.second){
      moves.emplace_back(pair<int,int>{x+1,y-1});
      moves.emplace_back(pair<int,int>{x,y-1});
      moves.emplace_back(pair<int,int>{x+1,y});
      moves.emplace_back(pair<int,int>{x-1,y-1});
      moves.emplace_back(pair<int,int>{x+1,y+1});
    } else {
      moves.emplace_back(pair<int,int>{x+1,y});
      moves.emplace_back(pair<int,int>{x+1,y-1});
      moves.emplace_back(pair<int,int>{x+1,y+1});
      moves.emplace_back(pair<int,int>{x,y-1});
      moves.emplace_back(pair<int,int>{x,y+1});
    }
  } else {
    if(y < playerPos.second){
      moves.emplace_back(pair<int,int>{x-1,y+1});
      moves.emplace_back(pair<int,int>{x,y+1});
      moves.emplace_back(pair<int,int>{x-1,y});
      moves.emplace_back(pair<int,int>{x-1,y-1});
      moves.emplace_back(pair<int,int>{x+1,y+1});
    } else if(y > playerPos.second){
      moves.emplace_back(pair<int,int>{x-1,y-1});
      moves.emplace_back(pair<int,int>{x,y-1});
      moves.emplace_back(pair<int,int>{x-1,y});
      moves.emplace_back(pair<int,int>{x-1,y+1});
      moves.emplace_back(pair<int,int>{x+1,y-1});
    } else {
      moves.emplace_back(pair<int,int>{x-1,y});
      moves.emplace_back(pair<int,int>{x-1,y-1});
      moves.emplace_back(pair<int,int>{x-1,y+1});
      moves.emplace_back(pair<int,int>{x,y-1});
      moves.emplace_back(pair<int,int>{x,y+1}); 
    }
  }
  for(unsigned int i = 0; i < moves.size(); ++i){
    if(moves.at(i).first < 0 || moves.at(i).second < 0 || 
        moves.at(i).first >= row || moves.at(i).second >= column) continue;
    shared_ptr<Tile> t = tileFloor[moves.at(i).first][moves.at(i).second];
    shared_ptr<ActiveTile> at = dynamic_pointer_cast<ActiveTile>(t);
    if(at == nullptr || at->hasPlayer() || at->hasItem()) continue;
    return moves.at(i);
  }
  return pair<int,int>{x,y};
}

void Floor::phoenixCount(){
  for(unsigned int i=0; i < deadPhoenix.size(); ++i){
    shared_ptr<ActiveTile> at = dynamic_pointer_cast<ActiveTile>(deadPhoenix.at(i));
    Phoenix &p = static_cast<Phoenix &>(at->getCharacter());
    if(p.getCount() == 0){
      // Resurrects Phoenix
      p.setHP(50);
      p.alive();
      deadPhoenix.at(i)->notifyObservers();
      deadPhoenix.erase(deadPhoenix.begin() + i);
    } else {
      p.setCount(p.getCount() - 1);
    }
  }
}

void Floor::init(){
  td = make_unique<TextDisplay>();
  for(int i=0; i < row; ++i){
      vector<shared_ptr<Tile>> rowVector;
      for(int j=0; j < column; ++j){
        CM val;
        if(!filePresent){
          val = defaultMap[i * column + j];
        } else {
          val = charMapFloor[i * column + j];
        }
        shared_ptr<Tile> tile = createTile(i, j, val);
        tile->attach(*td);
        tile->notifyObservers();
        rowVector.emplace_back(tile);
      }
      tileFloor.emplace_back(rowVector);
  }
  identifyChambers();
  if(!filePresent){
    // Locates a character
    int rn1 = randNumGen(numCham);
    int chamberSize1 = tileChamb[rn1].size();
    int rn2 = randNumGen(chamberSize1);
    pair<int, int> rcoord1 = tileChamb[rn1][rn2];
    playerInitialPosition = rcoord1;
    shared_ptr<Tile> t1 = tileFloor[rcoord1.first][rcoord1.second];
    // Creates a staircase
    int rn3 = randNumGen(numCham - 1);
    if(rn3 == rn1) ++rn3;
    int chamberSize2 = tileChamb[rn3].size();
    int rn4 = randNumGen(chamberSize2);
    pair<int, int> rcoord2 = tileChamb[rn3][rn4];
    shared_ptr<Tile> t2 = createTile(rcoord2.first, rcoord2.second, CM::Staircase);
    t2->attach(*td);
    tileFloor[rcoord2.first][rcoord2.second] = t2; 
    t2->notifyObservers();
    stairCoord.first = rcoord2.first;
    stairCoord.second = rcoord2.second;
    // Creates potions
    for(int i=0; i < numPots; ++i){
      int rn5 = randNumGen(numCham);
      int chamberSize3 = tileChamb[rn5].size();
      int rn6 = randNumGen(chamberSize3);
      pair<int, int> rcoord3 = tileChamb[rn5][rn6];
      shared_ptr<Tile> t = tileFloor[rcoord3.first][rcoord3.second];
      shared_ptr<ActiveTile> at = dynamic_pointer_cast<ActiveTile>(t);
      while(at == nullptr || at->hasPlayer() || at->hasItem()){
        rn6 = randNumGen(chamberSize3);
        rcoord3 = tileChamb[rn5][rn6];
        t = tileFloor[rcoord3.first][rcoord3.second];
        at = dynamic_pointer_cast<ActiveTile>(t);
      }
      int rn7 = randNumGen(numPotTotal);
      shared_ptr<Item> it = p->randomPot(rn7);
      at->attachItem(*it);
      vecItems.emplace_back(it);
    }
    // Creates golds
    for(int j=0; j < numGolds; ++j){
      int rn8 = randNumGen(numCham);
      int chamberSize4 = tileChamb[rn8].size();
      int rn9 = randNumGen(chamberSize4);
      pair<int, int> rcoord4 =  tileChamb[rn8][rn9];
      shared_ptr<Tile> t = tileFloor[rcoord4.first][rcoord4.second];
      shared_ptr<ActiveTile> at = dynamic_pointer_cast<ActiveTile>(t);
      while(at == nullptr || at->hasPlayer() || at->hasItem()){  
        rn9 = randNumGen(chamberSize4);
        rcoord4 = tileChamb[rn8][rn9];
        t = tileFloor[rcoord4.first][rcoord4.second];
        at = dynamic_pointer_cast<ActiveTile>(t);
      }
      int rn10 = randNumGen(numGoldTotal);
      shared_ptr<Item> it = p->randomGold(rn10);
      if(it->getType() == CM::DragonHorde){
        // Creates a dragon near the dragon horde
        vector<pair<int,int>> vp = vectorAround(rcoord4.first, rcoord4.second);
        int vps = static_cast<int>(vp.size());
        // Tests the edge cases (where Dragon cannot spawn near its horde)
        while(vps == 0){
          rn9 = randNumGen(chamberSize4);
          rcoord4 = tileChamb[rn8][rn9];
          t = tileFloor[rcoord4.first][rcoord4.second];
          at = dynamic_pointer_cast<ActiveTile>(t);
          vp = vectorAround(rcoord4.first, rcoord4.second);
          vps = static_cast<int>(vp.size());
        }
        int randn = randNumGen(vps);
        pair<int,int> dragCoord = vp[randn];
        shared_ptr<Tile> dragT = tileFloor[dragCoord.first][dragCoord.second];
        shared_ptr<ActiveTile> dragAt = dynamic_pointer_cast<ActiveTile>(dragT);
        auto drag = make_shared<Dragon>();
        drag->setHordePosition(rcoord4);
        vecEnemies.emplace_back(static_pointer_cast<Enemy>(drag));
        dragAt->attachCharacter(*static_pointer_cast<Base>(drag));
        --numEnemies;
      }
      vecItems.emplace_back(it);
      at->attachItem(*vecItems.back());
    }
    // Creates enemies
    for(int k=0; k < numEnemies; ++k){
      int rn11 = randNumGen(numCham);
      int chamberSize5 = tileChamb[rn11].size();
      int rn12 = randNumGen(chamberSize5);
      pair<int, int> rcoord5 = tileChamb[rn11][rn12];
      shared_ptr<Tile> t = tileFloor[rcoord5.first][rcoord5.second];
      shared_ptr<ActiveTile> at = dynamic_pointer_cast<ActiveTile>(t);
      while(at == nullptr || at->hasPlayer() || at->hasItem()){  
        rn12 = randNumGen(chamberSize5);
        rcoord5 = tileChamb[rn11][rn12];
        t = tileFloor[rcoord5.first][rcoord5.second];
        at = dynamic_pointer_cast<ActiveTile>(t);
      }
      int rn13 = randNumGen(numEnemTotal);
      shared_ptr<Base> bc = p->randomEnemy(rn13);
      at->attachCharacter(*bc);
      vecEnemies.emplace_back(static_pointer_cast<Enemy>(bc));
    }
  } else {
    // Associates each Dragon to its Dragon Horde
    // Creates a graph where an edge between the Dragon's coordinates and that of 
    // the Dragon Horde means that the Dragon is within 1 radius distance from 
    // the Dragon Horde
    vector<vector<pair<int, int>>> graph(dragonsCoordinate.size());
    int dragonIndex = 0;
    for (auto &dragonPos : dragonsCoordinate) {
      for (auto &hordePos : dragonHordesCoordinate) {
        if ((abs(dragonPos.first - hordePos.first) <= 1) &&
            (abs(dragonPos.second - hordePos.second) <= 1)) {
              graph[dragonIndex].emplace_back(hordePos);
            }
      }
      ++dragonIndex;
    }
    // Removes all Dragons that only have one possible Dragon Horde associated with it
    // Checks if there are dragons with more than one option for choosing its Dragon Horde
    if (graph.size() > 0) {
      graph = assignHordes(graph, 0);
    }
    dragonIndex = dragonsCoordinate.size() - 1;
    for (auto it = graph.rbegin(); it != graph.rend(); ++it) {
      if ((*it).size() == 1) {
        auto activeTile = static_pointer_cast<ActiveTile>(getTileByPair(dragonsCoordinate[dragonIndex]));
        auto dragon = static_cast<Dragon *>(&activeTile->getCharacter());
        dragon->setHordePosition((*it).back());
        graph.erase(it.base());
        dragonsCoordinate.erase(find(dragonsCoordinate.begin(), 
              dragonsCoordinate.end(), dragonsCoordinate.at(dragonIndex)));
      }
      --dragonIndex;
    }
  }
}

bool Floor::checkState(){
  if((race->getCoordinates().first == stairCoord.first) &&
      (race->getCoordinates().second == stairCoord.second)){
    return true;
  }
  return false;
}

void Floor::enemyVecMove() {
  int len = vecEnemies.size();
  int damage;
  // Sorts a vector of enemies (leftmost to rightmost, row by row)
  sort(vecEnemies.begin(), vecEnemies.end(), []( auto &left, auto &right ) {
      pair<int, int> leftPos = left->getCoordinates();
      pair<int, int> rightPos = right->getCoordinates();
      if (leftPos.first < rightPos.first) return true;
      if (leftPos.first == rightPos.first) return (leftPos.second < rightPos.second);
      else return false;
      });
  for(int i = 0; i < len; ++i) {
    shared_ptr<Enemy> moveEnemy = vecEnemies[i];
    if(vecEnemies[i]->isAlive() == false) continue; 
    if (moveEnemy->getType() == CM::Dragon){
      shared_ptr<Dragon> drag = dynamic_pointer_cast<Dragon>(moveEnemy);
      pair<int,int> hPos = drag->getHordePosition();
      if(!pcNearItem(hPos.first, hPos.second)) continue;
    }   // Doesn't respond if it's a Dragon and the Player is not near its horde. 
    damage = enemyMove(vecEnemies[i]);
    if(damage != -1) {
      if(race->getHP() <= 0) {
        td->sendMessage(make_tuple(MC::PlayerDied, CM::PC, 
              race->getGold(), racesInt[race->getRace()]));
        break;
      }
    }
  }
  sendInfoMessages();
}

int Floor::enemyMove(shared_ptr<Enemy> e) {
  pair<int, int> curCoordinate = e->getCoordinates();
  int damage = -1; // returns -1 if Enemy moved
  if(bonus && (e->getType() == CM::Troll)){
    shared_ptr<Enemy> enemy = e;
    shared_ptr<Troll> t = dynamic_pointer_cast<Troll>(enemy);
    t->regen();
  }
  if(e->checkRadius(*race) && e->getHostile()) { // checks to see if Player is within 1 radius
    int accuracy = 2;
    int rn_accuracy = randNumGen(accuracy);// accuracy check
    if(rn_accuracy == 0) {
      damage = e->attack(*race);
      int left = race->getHP() - damage;// sets Enemy HP
      if(left <= 0){
        race->setHP(0);
      } else {
        race->setHP(left);
      }
      td->sendMessage(make_tuple(MC::EnemyAttack, e->getType(), static_cast<float>(damage), race->getHP()));
    } else {
      damage = 0;// Enemy misses
      td->sendMessage(make_tuple(MC::EnemyAttack, e->getType(), static_cast<float>(damage), race->getHP()));
    }
  } else if (e->getType() != CM::Dragon) { // Player is not within 1 radius of enemy (excl. dragon)
    // checks whether the mode is default or bonus
    vector<pair<int, int>> vp = vectorAround(curCoordinate.first, curCoordinate.second);
    int vps = static_cast<int>(vp.size());
    if(vps <= 0) {
      return damage;
    } else {
      int rn = randNumGen(vps);
      pair<int, int> newPosition;
      if(bonus) {
        if(e->getType() == CM::Werewolf || e->getType() == CM::BabyHound){
          // pursues the player
          newPosition = pursuePlayer(curCoordinate.first, curCoordinate.second, true);
          if(newPosition.first == curCoordinate.first && newPosition.second == curCoordinate.second){
            newPosition = vp[rn];
          }
        } else if(e->getType() == CM::Goblin) {
            shared_ptr<Goblin> gob = dynamic_pointer_cast<Goblin>(e);
            if(gob->getStolen()>0){
              newPosition = pursuePlayer(curCoordinate.first, curCoordinate.second, false);
              if(newPosition.first == curCoordinate.first && newPosition.second == curCoordinate.second) {
              newPosition = vp[rn];
              }
            } else {
              newPosition = vp[rn];
            }
         } else {
          newPosition = vp[rn];
        }
      } else {
        newPosition = vp[rn]; 
      }
      shared_ptr<Tile> tile = getTileByPair(newPosition);
      shared_ptr<ActiveTile> activeTile = dynamic_pointer_cast<ActiveTile>(tile);
      static_pointer_cast<ActiveTile>(getTileByPair(curCoordinate))->detachCharacter();
      activeTile->attachCharacter(*e);
      e->setCoordinates(newPosition.first, newPosition.second);
    }
  }
  return damage;
}


void Floor::playerMove(string cmd){
  pair<int, int> curCoordinate = race->getCoordinates();
  pair<int, int> newPosition = getNewPosition(curCoordinate, cmd);
  shared_ptr<Tile> tile = getTileByPair(newPosition);
  shared_ptr<ActiveTile> activeTile = dynamic_pointer_cast<ActiveTile>(tile);
  td->sendMessage(make_tuple(MC::PlayerMove, CM::PC, 0, strDir[cmd]));
  int poison = race->poisonDamage();
  if (activeTile != nullptr) {
    CM tileType = activeTile->getType();
    if (tileType == CM::ActiveTile) {
      // Removes Player from the previous Tile
      static_pointer_cast<ActiveTile>(getTileByPair(curCoordinate))->detachCharacter();
      // Attaches to a new Tile
      activeTile->attachCharacter(*race);
      race->setCoordinates(newPosition.first, newPosition.second);
    } else if (tileType == CM::Treasure) {
      if (tileType != CM::DragonHorde) {
        race->useItem(activeTile->getItem());
        activeTile->detachItem();
        // Remove Player from the previous Tile
        static_pointer_cast<ActiveTile>(getTileByPair(curCoordinate))->detachCharacter();
        // Attach to new Tile
        activeTile->attachCharacter(*race);
      } else {
        auto dHorde = static_cast<DragonH &>(activeTile->getItem());
        if (dHorde.getAvailable()) {
          race->useItem(activeTile->getItem());
          activeTile->detachItem();
          static_pointer_cast<ActiveTile>(getTileByPair(curCoordinate))->detachCharacter();
          activeTile->attachCharacter(*race);
        }
      }
    } else {
      //There is a Potion or an Enemy on the Tile
    }
  } else if (tile->getType() == CM::Staircase) {
    // Player reached the end of the current Floor
    // Removes Player from the previour Tile
    race->setCoordinates(newPosition.first, newPosition.second);
    static_pointer_cast<ActiveTile>(getTileByPair(curCoordinate))->detachCharacter();
    if (floorNum == 5) {
      td->sendMessage(make_tuple(MC::PlayerWins, CM::PC, race->getGold(), racesInt[race->getRace()]));
    }
    // Now the board checks the state of the game to determine whether the Player 
    // reached the stair
  } else if (tile->getType() == CM::Door || tile->getType() == CM::Bridge) {
    // Removes Player from the previour Tile
    if(tile->getType() == CM::Door){
      static_pointer_cast<Door>(getTileByPair(curCoordinate))->detachCharacter();
      race->setCoordinates(newPosition.first, newPosition.second);
      static_pointer_cast<Door>(tile)->attachCharacter(*race);
    } else if (tile->getType() == CM::ActiveTile) {
      static_pointer_cast<ActiveTile>(getTileByPair(curCoordinate))->detachCharacter();
    } else {
      static_pointer_cast<Bridge>(getTileByPair(curCoordinate))->detachCharacter();
      race->setCoordinates(newPosition.first, newPosition.second);
      static_pointer_cast<Bridge>(tile)->attachCharacter(*race);
    }
    // Attaches to a new Tile
  } else {
    // Player tries to move to an invalid Tile
  }
  // bonus check for Phoenix 
  if(bonus) phoenixCount();
  if (poison > 0) {
    td->sendMessage(make_tuple(MC::PoisonAttack, CM::PC, 0.0, poison));
  }
}

void Floor::playerAttack(string cmd){
 pair<int, int> attackPosition = getNewPosition(race->getCoordinates(), cmd);
 shared_ptr<Tile> tile = getTileByPair(attackPosition);
 shared_ptr<ActiveTile> activeTile = dynamic_pointer_cast<ActiveTile>(tile);
 int damage;
 int HpLeft;
 CM tileType;
 int poison = race->poisonDamage();
 if(activeTile !=nullptr && activeTile->hasPlayer()) {
   tileType = activeTile->getType();
   if (tileType == CM::Enemy) { // There is an enemy
     damage =race->attack(activeTile->getCharacter()); // Calculates damage done on Enemy
     HpLeft = activeTile->getCharacter().getHP() - damage;
     if(HpLeft <= 0) HpLeft = 0;
     td->sendMessage(make_tuple(MC::PlayerAttack, tileType, static_cast<float>(damage), HpLeft));
     activeTile->getCharacter().setHP(HpLeft);// Sets Enemy's health
     if(tileType == CM::Merchant) {
       static_cast<Merchant &>(activeTile->getCharacter()).setHostile();
     } 
     if(activeTile->getCharacter().getHP() <= 0) {
         if(tileType != CM::Merchant && tileType != CM::Dragon) {
          race->updateGold(1); // Gets gold for non-merchant/non-dragon
         } else if (tileType == CM::Dragon) {
           Dragon &d = static_cast<Dragon &>(activeTile->getCharacter());
           pair<int, int> dHordePos = d.getHordePosition();
           shared_ptr<ActiveTile> dHordeTile = static_pointer_cast<ActiveTile>(getTileByPair(dHordePos));
           DragonH &dHorde = static_cast<DragonH &>(dHordeTile->getItem());
           dHorde.changeAvailability();
         }
         if(tileType == CM::Goblin && bonus) {
           Goblin &g = static_cast<Goblin &>(activeTile->getCharacter());
           int dropped = g.getStolen();
           race->updateGold(dropped);
         }
         if(tileType == CM::Phoenix && bonus){
           Phoenix &p = static_cast<Phoenix &>(activeTile->getCharacter());
           p.died(); // Phoenix becomes Ash
           deadPhoenix.emplace_back(tile);
           tile->notifyObservers();
         } else {
           static_pointer_cast<ActiveTile>(tile)->detachCharacter();// Remove the Enemy from Tile
         } 
         if(tileType == CM::Merchant){
           shared_ptr<Item> mgold = make_shared<MerchantH>();
           static_pointer_cast<ActiveTile>(tile)->attachItem(*mgold);// Attaches Merchant Horde
           vecItems.emplace_back(mgold);
         } else if (tileType == CM::Cerberus){ 
           // need not to check if the mode is a bonus since the Cerberus only spawns in the bonus
           // spawns max number of 3 BabyHounds around the Player upon the death of Cerberus
           pair<int,int> playerCoord = race->getCoordinates();
           vector<pair<int,int>> vp = vectorAround(playerCoord.first, playerCoord.second);
          int vps = static_cast<int>(vp.size());
          // tests the edge cases (where BabyHounds cannot be spawned near the Player)
          if(vps == 0){
            // cannot spawn; don't spawn any BabyHounds
          } else if (1 <= vps && vps <= 3){
            for(unsigned int k=0; k < vp.size(); ++k){
              shared_ptr<Tile> houndT = tileFloor[vp.at(k).first][vp.at(k).second];
              shared_ptr<ActiveTile> houndAt = dynamic_pointer_cast<ActiveTile>(houndT);
              auto hound = make_shared<BabyHound>();
              vecEnemies.emplace_back(static_pointer_cast<Enemy>(hound));
              houndAt->attachCharacter(*static_pointer_cast<Base>(hound));
            }
          } else {
            int randPos = static_cast<int>(vp.size());
            vector<int> vi;
            for(int i=0; i < 3; ++i){
              vi.emplace_back(randNumGen(randPos - i));
            }
            if(vi[0] == vi[1]){
              vi[1] += 1;
            }
            if(vi[0] == vi[2]){
              vi[2] += 2;
            }
            if(vi[1] == vi[2]){
              vi[2] += 1;
            }
            for(int i=0; i < 3; ++i){
              pair<int,int> pi = vp[vi[i]];
              shared_ptr<Tile> houndT = tileFloor[pi.first][pi.second];
              shared_ptr<ActiveTile> houndAt = dynamic_pointer_cast<ActiveTile>(houndT);
              auto hound = make_shared<BabyHound>();
              vecEnemies.emplace_back(static_pointer_cast<Enemy>(hound));
              houndAt->attachCharacter(*static_pointer_cast<Base>(hound));
            }
          } 
         } else if(tileType == CM::Witch) { // bonus Enemy
            // spawns a Restore Health potion (cures the poison effect)
            shared_ptr<Item> it = make_shared<RestoreH>();
            static_pointer_cast<ActiveTile>(tile)->attachItem(*it);
            vecItems.emplace_back(it);
          }
         }
     } else {
       //does nothing as there is no Enemy
       td->sendMessage(make_tuple(MC::PlayerAttack, CM::ActiveTile, 0.0, 0));
     }
   } else {
     td->sendMessage(make_tuple(MC::PlayerAttack, CM::ActiveTile, 0.0, 0));
 }
 if (poison > 0) {
   td->sendMessage(make_tuple(MC::PoisonAttack, CM::PC, 0.0, poison));
 }
 // bonus check for Phoenix
 if(bonus) phoenixCount();
}


void Floor::checkPotion() {
  pair<int, int> newPosition;
  bool hidden = true;
  vector<tuple<CM, bool, bool>> potionVec;
  td->sendMessage(make_tuple(MC::PlayerMoveCons, CM::ActiveTile, static_cast<float>(hidden), 0));
  for(int i = 0; i < neighborTiles; ++i) {
    newPosition = getNewEnemyPos(race->getCoordinates(), i);
    shared_ptr<Tile> tile = getTileByPair(newPosition);
    shared_ptr<ActiveTile> activeTile = dynamic_pointer_cast<ActiveTile>(tile);
    if(activeTile != nullptr) {
      CM tileType = activeTile->getType();
      if (tileType == CM::Potion) {
        Potion &p = static_cast<Potion &>(activeTile ->getItem());
        hidden = p.getHidden();
        td->sendMessage(make_tuple(MC::PlayerMoveCons, tileType, static_cast<float>(hidden), 0));
      } else {
        continue;
      }
    } else {
      continue;
    }
  }
}

void Floor::playerPot(string cmd){
  int poison = race->poisonDamage();
  pair<int, int> potPosition = getNewPosition(race->getCoordinates(), cmd);
  shared_ptr<Tile> tile = getTileByPair(potPosition);
  shared_ptr<ActiveTile> activeTile = dynamic_pointer_cast<ActiveTile>(tile);
  if(activeTile != nullptr) {
    CM tileType = activeTile->getType();
    if (tileType == CM::Potion) {
      Item &i = activeTile->getItem();
      race->useItem(i);
      static_pointer_cast<ActiveTile>(tile)->detachItem();
      static_pointer_cast<ActiveTile>(getTileByPair(race->getCoordinates()))->detachCharacter();
      race->setCoordinates(potPosition.first, potPosition.second);
      activeTile->attachCharacter(*race);
      int cured = 0;
      if(tileType == CM::RH && poison > 0) {
        cured = poison;
        poison = 0;
        int hp = race->getHP() + 5;
        int max = race->getMaxHP();
        if(hp > max) {
          hp = max;
        }
        race->setHP(hp);
      }
      td->sendMessage(make_tuple(MC::UsePotion, tileType, 0.0, cured));
    } else { 
      td->sendMessage(make_tuple(MC::UsePotion, CM::ActiveTile, 0.0, 0));
    }
  } else {
    td->sendMessage(make_tuple(MC::UsePotion, CM::ActiveTile, 0.0, 0));
  }
  // signals that there is no Potion to be found
  if (poison > 0) {
    td->sendMessage(make_tuple(MC::PoisonAttack, CM::PC, 0.0, poison));
  }
  // check bonus for Phoenix
  if(bonus) phoenixCount();
}

pair<int, int> Floor::getPlayerInitialPosition() const {
  return playerInitialPosition;
}

ostream &operator<<(ostream &out, const Floor &f){
  out << *f.td;
  return out;
}

pair<int, int> getNewEnemyPos(const pair<int, int> &curPosition, int direction) {
  pair<int, int> newPosition{curPosition};
  if(direction == 0){
   //Moves North
   --newPosition.first;}
  if(direction == 1) {
    //Moves Northeast
    --newPosition.first;
    ++newPosition.second;}
  if(direction == 2) {
    //Moves Northwest
    --newPosition.first;
    --newPosition.second;}
  if(direction == 3) {
    //Moves South
      ++newPosition.first;}
  if(direction ==4) {
    //Moves Southeast
    ++newPosition.first;
    ++newPosition.second;}
  if(direction == 5) {
    //Moves Southwest
    ++newPosition.first;
    --newPosition.second;}
  if(direction == 6) {
    //Moves West
    --newPosition.second;}
  if(direction == 7) {
    //Moves East
    ++newPosition.second;}
  return newPosition;
}

pair<int, int> getNewPosition(const pair<int, int> &curPosition, const string &direction) {
  pair<int, int> newPosition{curPosition};
  if (direction[0] == 'n') {
    // Moves north
    --newPosition.first;
    if (direction[1] == 'e') {
      // Moves east
      ++newPosition.second;
    } else if (direction[1] == 'w') {
      // Moves west
      --newPosition.second;
    }
  } else if (direction[0] == 's') {
    // Moves south
    ++newPosition.first;
    if (direction[1] == 'e') {
      // Moves east
      ++newPosition.second;
    } else if (direction[1] == 'w') {
      // Moves west
      --newPosition.second;
    }
  } else if (direction == "ea") {
    // Moves east
    ++newPosition.second;
  } else if (direction == "we") {
    // Moves west
    --newPosition.second;
  }
  return newPosition;
}

vector<vector<pair<int, int>>> assignHordes(vector<vector<pair<int, int>>> &graph, int dragonIndex) {
  if (static_cast<unsigned int>(dragonIndex) == graph.size()) return graph;
  for (auto it = graph[dragonIndex].begin(); it != graph[dragonIndex].end(); ++it) {
    vector<vector<pair<int, int>>> auxGraph{graph}; // Copies the graph of asscoiation captured above
    // Chooses one of the possible Dragon Hordes
    auxGraph[dragonIndex].clear();
    auxGraph[dragonIndex].emplace_back(*it);
    // Removes a chosen Dragon Horde from other Dragons
    for (unsigned int i = dragonIndex + 1; i < graph.size(); ++i) {
      for (auto rit = auxGraph[i].rbegin(); rit != auxGraph[i].rend(); ++rit) {
        if (*rit == *it) {
          auxGraph[i].erase(--rit.base());
        }
      }
    }
    auxGraph = assignHordes(auxGraph, dragonIndex + 1);
    if (auxGraph.size() > 0) return auxGraph;
  }
  return {};
}
