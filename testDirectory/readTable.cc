#include "defaultMap.h"
#include <iostream>

using namespace std;

int main() {
  int i = 0;
  for (auto &code : defaultMap) {
    if ((i % 79 == 0) && (i != 0)) cout << '\n';
    ++i;
    cout << code << ' ';
  }
  cout << '\n';
  return 0;
}
