#include "board.h"
#include <iostream>
using namespace std;
class Floor { };

class Player {  };

class Potion { };

int main(){
	Board b;
	b.updateGold(10);
	int score = b.getScore();
	int randomNum1 = b.randNumGen(5);
	int randomNum2 = b.randNumGen(5);
	cout << score << endl;
	cout << randomNum1 << randomNum2 << endl;
	return 0;
}

