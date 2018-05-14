#include "../interpreter.h"
#include "../board.h"

int main() {
  Interpreter i;
  Board b{};
  i.interpretCommands(b);
  return 0;
}
