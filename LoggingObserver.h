#pragma once

#include <iostream>
#include <list>

class Observer;
class Subject;
class ILoggable;
class LogObserver;

void testLoggingObserver();

class Observer{
public:
    Observer();
    ~Observer();
    Observer(const Observer& o1);
    Observer& operator=(const Observer& o1);
    friend std::ostream& operator<<(std::ostream&, const Observer&);
    virtual void update(ILoggable* il) = 0;
};

class LogObserver : public Observer{
public:
    LogObserver();
    ~LogObserver();
    LogObserver(const LogObserver& lo);
    LogObserver& operator=(const LogObserver& lo);
    friend std::ostream& operator<<(std::ostream&, const LogObserver&);
    void update(ILoggable* il);
};

class Subject{
public:
    Subject();
    ~Subject();
    Subject(const Subject& s1);
    Subject& operator=(const Subject& s1);
    friend std::ostream& operator<<(std::ostream&, const Subject&);
    void notify(ILoggable* il);
    void attach(Observer* o);
    void detach(Observer* o);
private:
    std::list<Observer*> *_observers;
};

class ILoggable{
public:
    ILoggable();
    ~ILoggable();
    ILoggable(const ILoggable& il);
    ILoggable& operator=(const ILoggable& il);
    friend std::ostream& operator<<(std::ostream&, const ILoggable&);
    virtual std::string stringToLog() = 0;
};


