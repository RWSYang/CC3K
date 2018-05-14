#include<ncurses.h>
#include<iostream>
#include<curses.h>
using namespace std;

int main() {
  initscr();
//  keypad(stdscr,true);
  refresh();
  WINDOW* w;
  w = newwin(10,10,10,10);
  endwin();
  return 0;
}
