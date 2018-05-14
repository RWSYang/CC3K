#include <fstream>
#include "interpreter.h"
#include "board.h"
#include "layoutparser.h"
using namespace std;

int main(int argc, char *argv[]) {
  Interpreter I;
  if(argc == 1){
    Board b;
    I.interpretCommands(b);
  } else if (argc == 2){
    ifstream file {argv[argc - 1]};
    LayoutParser lp(file);
    Board b{lp.parseFile()};
    I.interpretCommands(b);
  }
}

