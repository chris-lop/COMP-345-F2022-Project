#pragma once

#include <iostream>
#include <list>

// class forward declarations
class Observer;
class Subject;
class ILoggable;
class LogObserver;

// free function
void testLoggingObserver(std::string command);
// static variable to know if the game just started running
static bool empty = true;

// Observer class
class Observer
{
public:
    // constructor
    Observer();
    // destructor
    ~Observer();
    // copy constructor
    Observer(const Observer &o1);
    // assignment operator
    Observer &operator=(const Observer &o1);
    // stream insertion
    friend std::ostream &operator<<(std::ostream &, const Observer &);
    // pure virtual update method which writes to the log file
    virtual void update(ILoggable *il) = 0;
};

class LogObserver : public Observer
{
public:
    // constructor

    LogObserver();
    // destructor
    ~LogObserver();
    // copy constructor
    LogObserver(const LogObserver &lo);
    // assignment operator
    LogObserver &operator=(const LogObserver &lo);
    // stream insertion
    friend std::ostream &operator<<(std::ostream &, const LogObserver &);
    // update method which writes to the log file
    void update(ILoggable *il);
};

class Subject
{
public:
    // constructor

    Subject();
    // destructor
    ~Subject();
    // assignment operator
    Subject &operator=(const Subject &s1);
    // copy constructor
    Subject(const Subject &s1);
    // stream insertion
    friend std::ostream &operator<<(std::ostream &, const Subject &);
    // notfy(this) method which notifies the observer
    void notify(ILoggable *il);
};

class ILoggable
{
public:
    // constructor

    ILoggable();
    // destructor
    ~ILoggable();
    // assignment operator
    ILoggable &operator=(const ILoggable &il);
    // copy constructor
    ILoggable(const ILoggable &il);
    // stream insertion
    friend std::ostream &operator<<(std::ostream &, const ILoggable &);
    // pure virtual stringToLog function in order to take strings and tansform to logs
    virtual std::string stringToLog() = 0;
};
