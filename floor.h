#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <vector>
#include <iostream>
#include <memory>
#include <set>
#include <tuple>
#include <string>
#include <utility>
#include "charactersMapping.h"

class Player;
class Probability;
class Enemy;
class Item;
class Phoenix;
class TextDisplay;
class Tile;

class Floor {
  std::vector<std::vector<std::shared_ptr<Tile>>> tileFloor;
  std::vector<std::vector<std::pair<int,int>>> tileChamb;
  const int floorNum;
  const int row = 25;
  const int column = 79;
  static bool flag;
  bool bonus;
  const int numCham = 5;
  std::vector<std::shared_ptr<Enemy>> vecEnemies;
  std::vector<std::shared_ptr<Item>> vecItems;
  int numEnemies = 20;
  const int numEnemTotal = 18;
  const int numPots = 10;
  const int numPotTotal = 6;
  const int numGolds = 10;
  const int numGoldTotal = 8;
  const int neighborTiles = 8;
  const int radius = 5;
  std::pair<int, int> stairCoord;
  std::shared_ptr<Player> race;
  std::unique_ptr<Probability> p;
  std::vector<CM> charMapFloor;
  std::shared_ptr<TextDisplay> td;
  int randNumGen(int total);
  void setFlag();
  bool filePresent = false;
  std::pair<int, int> playerInitialPosition;
  std::vector<std::pair<int, int>> dragonsCoordinate;
  std::vector<std::pair<int, int>> dragonHordesCoordinate;
  std::vector<std::shared_ptr<Tile>> deadPhoenix;
  void identifyChambers();
  void exploreSurroundings(std::pair<int, int> coordinate, 
      std::set<std::pair<int, int>> &visitedTiles, int chamberNumber);
  // Get Tile using a pair of coordinates
  std::shared_ptr<Tile> getTileByPair(std::pair<int, int> pair);
  std::shared_ptr<Tile> createTile(int x, int y, CM type);
  std::vector<std::pair<int,int>> vectorAround(int x, int y);
  bool pcNearItem(int x, int y);
  std::pair<int,int> pursuePlayer(int x, int y, bool chase);
  void phoenixCount();
  void sendInfoMessages() const;
  public:
    Floor(int floorNum, bool bonus);
    Floor(int floorNum, bool bonus, std::vector<CM>& vcm);
    ~Floor();
    void setPlayer(std::shared_ptr<Player> p);
    void init();
    bool checkState();
    void enemyVecMove();
    int enemyMove(std::shared_ptr<Enemy>);
    void playerMove(std::string cmd);
    void playerAttack(std::string cmd);
    void playerPot(std::string cmd);
    void checkPotion();
    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
    std::pair<int, int> getPlayerInitialPosition() const;
};

std::pair<int, int>getNewEnemyPos(const std::pair<int, int> &curPosition, int direction);
std::pair<int, int> getNewPosition(
    const std::pair<int, int> &curPosition, const std::string &direction);
std::vector<std::vector<std::pair<int, int>>> assignHordes(
    std::vector<std::vector<std::pair<int, int>>> &graph, int dragonIndex);

#endif
