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
    if(empty){
        ofstream logFile("gamelog.txt", std::ios::trunc);
        logFile << il->stringToLog() << endl;
        logFile.close();
        empty = false;
    }
    else{
        ofstream logFile("gamelog.txt", std::ios::app);
        logFile << il->stringToLog() << endl;
        logFile.close();
    }
}

//Class Subject
Subject::Subject(){
}

Subject::~Subject(){ 
    // delete this->_observer;
}

void Subject::attach(Observer* o){
    // this->_observer = o;
}

void Subject::detach(Observer* o){
    // this->_observer = nullptr;
}

void Subject::notify(ILoggable* il){
    LogObserver* observer = new LogObserver();
    observer->update(il);
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