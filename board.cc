#include "board.h"
#include "tile.h"
#include "potion.h"
#include "human.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"
#include <iostream>
using namespace std;

Board::Board(): bonus{false}, curFloor{1} { }

Board::Board(const vector<vector<CM>>& vvcm): 
  bonus{false}, parsedResult{vvcm}, curFloor{1} { }

void Board::bonusMode() {
  bonus = true;
}

void Board::notBonusMode() {
  bonus = false;
}

void Board::init() {
  if (parsedResult.size() > 0) {
    for(int i=0; i < floorNum; ++i){
      vecFloors.emplace_back(make_unique<Floor>(i + 1, bonus,parsedResult.at(i)));
      vecFloors[i]->init();
    }
  } else {
    for (int i = 0; i < floorNum; ++i) {
      vecFloors.emplace_back(make_unique<Floor>(i + 1, bonus));
      vecFloors[i]->init();
    }
  }
  vecFloors[0]->setPlayer(race);
}

void Board::createPlayer(string pc){
  player = pc;
  if (pc == "h") {
    race = static_pointer_cast<Player>(make_shared<Human>());
  } else if (pc == "e") {
    race = static_pointer_cast<Player>(make_shared<Elf>());
  } else if (pc == "o") {
    race = static_pointer_cast<Player>(make_shared<Orc>());
  } else if (pc == "d") {
    race = static_pointer_cast<Player>(make_shared<Dwarf>());
  } else {
    return;
  }

  init();
}

pair<bool,bool> Board::checkState() {
  pair<bool,bool> state; // first bool checks whether the game ended
                        // When first bool is true,
                       // second bool checks how the game ended
  state.first = false;
  state.second = false;
  if(vecFloors.at(curFloor - 1)->checkState()){
    if(curFloor == floorNum){
      state.first = true; 
      // game ended by finishing the fifth floor
    } else {
      ++curFloor;
      race->resetAtkDef();
      state.second = true; // moved to the next floor
      vecFloors[curFloor - 1]->setPlayer(race);
    }
  } else if (race->getHP() <= 0){
    state.first = true;
    state.second = true;
    // game ended by losing all the health of a player
  }
	return state;
}

void Board::enemyMove(){
  vecFloors.at(curFloor - 1)->enemyVecMove();
}

void Board::playerMove(string cmd){
  vecFloors.at(curFloor - 1)->playerMove(cmd);
}

void Board::playerAttack(string cmd){
  vecFloors.at(curFloor - 1)->playerAttack(cmd);
}

void Board::playerPot(string cmd){
  vecFloors.at(curFloor - 1)->playerPot(cmd);
}

void Board::checkPot() {
  vecFloors.at(curFloor -1)->checkPotion();
}

void Board::printFloor() {
  cout << *vecFloors[curFloor - 1];
}

void Board::reset() {
  vecFloors.clear();
  race.reset();
  curFloor=1;
}
