#ifndef __SUBJECT_H__
#define __SUBJECT_H__
class Observer;

class Subject {
  public:
    Subject() = default;
    virtual void attach(Observer &ob) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

#endif
