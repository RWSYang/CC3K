#ifndef __TILE_H__
#define __TILE_H__

#include <vector>
#include <utility>
#include "charactersMapping.h"
#include "subject.h"

class Tile: public Subject {
    std::vector<Observer *> observers;
    std::pair<int, int> coordinate;
  public:
    Tile(int x, int y);
    virtual ~Tile() = default;
    std::pair<int, int> getCoordinates() const;
    virtual void attach(Observer &ob) override;
    virtual void notifyObservers() override;
    virtual CM getType() const = 0;
};

#endif
