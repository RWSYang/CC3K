#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include "floor.h"
#include "layoutparser.h"
#include "charactersMapping.h"
#include "codeConversion.h"

class Potion;
class Player;

class Board {
  const int floorNum = 5;
  bool bonus;
	std::vector<std::unique_ptr<Floor>> vecFloors;
  std::vector<std::vector<CM>> parsedResult;
	int curFloor;
  std::shared_ptr<Player> race;
  std::string player = "h"; 
  void init();
  public:
    Board();
    Board(const std::vector<std::vector<CM>>& vvcm);
		~Board() = default;
    void bonusMode();
    void notBonusMode();
    void createPlayer(std::string race);
    std::pair<bool,bool> checkState();
    void enemyMove();
		void playerMove(std::string cmd);
    void checkPot();
    void playerAttack(std::string cmd);
    void playerPot(std::string cmd);
    void printFloor();
    void reset();
};

#endif
