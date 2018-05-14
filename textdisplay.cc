#include "textdisplay.h"
#include <iostream>
#include <utility>
#include "tile.h"
#include "messagesCode.h"
#include <algorithm>
#include "codeConversion.h"

using namespace std;

TextDisplay::TextDisplay() {
  for (int i = 0; i < totalChar; ++i) {
    char c = ' ';
    txtDisplay.emplace_back(c);
  }
}

void TextDisplay::notify(Tile &t){
  pair<int,int> coord = t.getCoordinates();
  char tchar = cmConversion[t.getType()];
  txtDisplay[coord.first*colNum + coord.second] = tchar;
}

void TextDisplay::sendMessage(tuple<MC, CM, float, int> message) {
  messages.emplace_back(message);
}

ostream &operator<<(ostream &out, const TextDisplay &td){
  for(int i=0; i < td.rowNum; ++i){
    for(int j=0; j < td.colNum; ++j){
      out << td.txtDisplay[i*td.colNum + j];
    }
    out << "\n";
  }
  sort(td.messages.begin(), td.messages.end(), [](auto &left, auto &right) {
      return static_cast<int>(get<0>(left)) > static_cast<int>(get<0>(right));
      });
  while (td.messages.size() > 0) {
    const tuple<MC, CM, float, int>  &m = td.messages.back();
    td.messages.pop_back();
    out << td.printMessage(m);
    if (get<0>(m) == MC::PlayerDied || get<0>(m) == MC::PlayerWins) {
      td.messages.clear();
    }
  }
  out << '\n';

  return out;
}

string TextDisplay::printMessage(const tuple<MC, CM, float, int> &m) const {
  MC messageCode;
  CM charMap;
  float fValue;
  int extra;
  tie(messageCode, charMap, fValue, extra) = m;
  int iValue = static_cast<int>(fValue);

  switch(messageCode) {
    case MC::PlayerDied:
      {
        if (intRaces[extra] == "Human") {
          fValue *= 1.5;
          iValue = static_cast<int>(fValue);
        }
        string g = to_string(iValue);
        if (fValue > static_cast<float>(iValue)) {
          g += ".5";
        }
        return "Player died!\nFinal score: " + g;
      }
    case MC::PlayerWins:
      {
        if (intRaces[extra] == "Human") {
          fValue *= 1.5;
          iValue = static_cast<int>(fValue);
        }
        string g = to_string(iValue);
        if (fValue > static_cast<float>(iValue)) {
          g += ".5";
        }
        return "Congratulations, you won the game!\nFinal score: " + g;
      }
      break;
    case MC::PlayerRace:
      return "Race: " + intRaces[extra] + " ";
      break;
    case MC::PlayerGold:
      {
        string g = to_string(iValue);
        if (fValue > static_cast<float>(iValue)) {
          g += ".5";
        }
        return "Gold: " + g;
      }
      break;
    case MC::CurrentFloor:
      return string(50, ' ') + "Floor: " + to_string(iValue) + "\n";
      break;
    case MC::PlayerHP:
      return "HP: " + to_string(iValue) + "\n";
      break;
    case MC::PlayerATK:
      return "Atk: " + to_string(iValue) + "\n";
      break;
    case MC::PlayerDEF:
      return "Def: " + to_string(iValue) + "\n";
      break;
    case MC::PlayerSpawn:
      if (iValue == 1) {
        return "Action: Player character (" + intRaces[extra] + ") has spawned.";
      } else {
        return "PC entered floor level " + to_string(iValue) + "!";
      }
      break;
    case MC::PlayerMove:
      return "Action: PC moves " + intDir[extra];
      break;
    case MC::PlayerMoveCons:
      if (charMap != CM::ActiveTile) {
        if (iValue) {
          return " and sees an unknown potion";
        } else {
          return " and sees " + potions[charMap];
        }
      } else {
        return ". ";
      }
      break;
    case MC::PlayerAttack:
      if (charMap != CM::ActiveTile) {
        return "Action: PC deals " + to_string(iValue) + " to " + enemies[charMap] + " (" + to_string(extra) + " HP). ";
      } else {
        return "Action: PC attacks nothing. ";
      }
      break;
    case MC::UsePotion:
      if (charMap != CM::ActiveTile) {
        string out= "Action: PC uses " + potions[charMap]+ " ";
        if(charMap == CM::RH && extra > 0) {
          return out + "your poison is now healed ";
        } else {
          return out;
        }
      } else {
        return "There is no potion to use! ";
      }
    case MC::EnemyAttack:
      {
        if (iValue == 0) { // Enemy missed attack
          return enemies[charMap] + " misses its attack! ";
        } else if (iValue > 0) {
          return enemies[charMap] + " deals " + to_string(iValue) + " damage to PC (" + to_string(extra) + " HP). ";
        }
      }
      break;
    case MC::PoisonAttack:
      return "You have been affected by poison. You have " + to_string(extra) + " turn of poison left.";
  }
  return "";
}
