#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__
#include <string>
#include "charactersMapping.h"

class Board;

class Interpreter {
  public:
    Interpreter();
    ~Interpreter();
    void interpretCommands(Board &b);
  private:
    std::string welcomeMessage;
    std::string optionMode;
    std::string optionPlayer;
};

#endif
