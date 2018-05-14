#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector>
#include <string>
#include <tuple>
#include "observer.h"
#include "charactersMapping.h"
#include "messagesCode.h"

class TextDisplay: public Observer {
  const int rowNum = 25;
  const int colNum = 79;
  const int totalChar = rowNum * colNum;
  std::vector<char> txtDisplay;
  mutable std::vector<std::tuple<MC, CM, float, int>> messages;
  std::string printMessage(const std::tuple<MC, CM, float, int> &m) const;
  public:
    TextDisplay();
    ~TextDisplay() = default;
    void notify(Tile &t);
    void sendMessage(std::tuple<MC, CM, float, int> message);
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
