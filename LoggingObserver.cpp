#include <iostream> 
#include <algorithm>
#include <fstream>
#include "LoggingObserver.h"

using std::cout; 
using std::string; 
using std::list;
using std::endl;
using std::ofstream;


//Observer class
Observer::Observer(){
}

Observer::~Observer(){
}

Observer::Observer(const Observer& o1){
}

Observer& Observer::operator=(const Observer& o1){
    return *this;
}

std::ostream& operator<<(std::ostream &strm, const Observer &o){
    return strm;
}


//class LogObserver
LogObserver::LogObserver(){
}

LogObserver::~LogObserver(){
}

LogObserver::LogObserver(const LogObserver& lo){
}

LogObserver& LogObserver::operator=(const LogObserver& lo){
    return *this;
}

std::ostream& operator<<(std::ostream &strm, const LogObserver &lo){
    return strm;
}

void LogObserver::update(ILoggable* il){
    //write into log file
    ofstream logFile("gamelog.txt");
    logFile << il->stringToLog() << endl;
    logFile.close();
}

//Class Subject
Subject::Subject(){
   this->_observers = new list<Observer*>;
}

Subject::~Subject(){ 
    delete this->_observers;
}

void Subject::attach(Observer* o){
    this->_observers->push_back(o);
}

void Subject::detach(Observer* o){
    this->_observers->remove(o);
}

void Subject::notify(ILoggable* il){
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
    (*i)->update(il);
}

//Class ILoggable
ILoggable::ILoggable(){
}

ILoggable::~ILoggable(){
}

ILoggable::ILoggable(const ILoggable& il){
}

ILoggable& ILoggable::operator=(const ILoggable& il){
    return *this;
}

std::ostream& operator<<(std::ostream &strm, const ILoggable &il){
    return strm;
}