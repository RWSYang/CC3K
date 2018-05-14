#include "interpreter.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include "codeConversion.h"

using namespace std;

Interpreter::Interpreter() {
  welcomeMessage = "\n***** Welcome to CC3k! *****\n\n";
  optionMode = "Please choose a game mode.\n\
  d : Default\n\
  b : Bonus\n\n";
  optionPlayer = "\nPlease choose a race.\n\
  h : Human\n\
  e : Elf\n\
  d : Dwarf\n\
  o : Orc\n\n";
}

Interpreter::~Interpreter() { }

void Interpreter::interpretCommands(Board &b) {
  bool beganM = false, beganP = false, ended = false;
  string cmd;
  cout << welcomeMessage << optionMode;
  while (true) {
    if(!ended){
      cin >> cmd;
    }
    if (beganM == false) {
      // checks a chosen mode for the game
      if(cmd == "b" || cmd == "d"){
        if(cmd == "b") b.bonusMode();
        if(cmd == "d") b.notBonusMode();
        beganM = true;
        cout << optionPlayer;
      } else {
        cout << "Please enter a valid mode." << endl;
      }
    } else if(beganP == false) {
      // checks a chosen race for the game
      if (races.count(cmd)) {
        // First display of a generated board
        beganP = true;
        b.createPlayer(cmd);
        b.printFloor();
      } else {
        cout << "Please select a valid race.\n";
      }
    } else if (directions.count(cmd)) {
      // Displays the player's movement
      b.playerMove(cmd);
      b.enemyMove();
      b.checkPot();
      b.printFloor();
    } else if (cmd == "a") {
      // Attacks an enemy in the given direction
      string direction;
      cin >> direction;
      if (directions.count(direction)) {
        // Player attacks enemy
        b.playerAttack(direction);
        b.enemyMove();
        b.printFloor();
      }
    } else if (cmd == "u") {
      // Uses an item in the given direction
      string direction;
      cin >> direction;
      if (directions.count(direction)) {
        // Player uses item
        b.playerPot(direction);
        b.enemyMove();
        b.printFloor();
      }
    } else if (cmd == "r") {
      cout << "Restarting the game\n";
      beganM = false;
      beganP = false;
      ended = false;
      b.reset();
      cout << welcomeMessage << optionMode;
      // Reset board
    } else if (cmd == "q") {
      cout << "Finishing the game\n";
      // Finish game
      break;
    } 
    if (beganM && beganP) {
      // After the mode and race selections, check a state of the game
      pair<bool,bool> state = b.checkState();
      if(state.first){
        cout << "Press r to Restart or q to Quit" << endl;
        while(cin >> cmd){
          ended = true;
          if(cmd == "r" || cmd == "q") break;
          cout << "Please enter a valid command." << endl;
        }
      } else if (state.second) {
        // Entered a new floor
        b.printFloor();
      }
    }
    if (cin.fail()) break;
  }
  b.reset();
}
