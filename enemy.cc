#include "enemy.h"
#include "player.h"

using namespace std;

Enemy::Enemy(int health, int attack, int defense, std::string type): 
  Base(health, attack, defense, type) {}

Enemy::~Enemy() { }

bool Enemy::isAlive() {
  if(this->getHP() <=0) {
    return false;
  } else {
    return true;
  }
}

bool Enemy::checkRadius(Player &p) {
  std::pair <int, int> p_coords (p.getCoordinates());
  int player_x = p_coords.first;
  int player_y = p_coords.second;
  std::pair <int, int> e_coords (this->getCoordinates());
  int enemy_x = e_coords.first;
  int enemy_y = e_coords.second;
  int x_length=enemy_x - player_x;
  int y_length = enemy_y - player_y;
  if(x_length == 0) {
    if(y_length == -1 || y_length == 1) {
      return true;
    } else {
      return false;
    }
  } else if(y_length == 0) {
    if(x_length == -1 || x_length == 1) {
      return true;
    } else {
      return false;
    }
  } else if(x_length == 1 || x_length == -1) {
    if(y_length == 1 || y_length == -1) {
      return true;
    } else {
      return false;
    }
  } else if(y_length == 1 || y_length == -1) {
    if(x_length == 1 || x_length == -1) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Enemy::getHostile() const {
  return true;
}

void Enemy::setHostile() { }
