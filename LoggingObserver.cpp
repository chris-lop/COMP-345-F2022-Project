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
//Observer constructor
Observer::Observer(){
}

//Observer destructor
Observer::~Observer(){
}

//Observer assignment operation
Observer& Observer::operator=(const Observer& c1){
	return *this;
}

//observer copy constructor
Observer::Observer(const Observer& o1){
}

//observer stream insertion
std::ostream& operator<<(std::ostream &strm, const Observer &o){
    return strm;
}


//class LogObserver
//LogOberver constructor
LogObserver::LogObserver(){
}

//LogOberver destructor
LogObserver::~LogObserver(){
}

//LogOberver copy constructor
LogObserver::LogObserver(const LogObserver& lo){
}

//LogOberver assignment operator
LogObserver& LogObserver::operator=(const LogObserver& lo){
    return *this;
}

//LogOberver insertion stream
std::ostream& operator<<(std::ostream &strm, const LogObserver &lo){
    return strm;
}

//LogOberver upadate method which writes the stringToLog() into a file
void LogObserver::update(ILoggable* il){
    //Check if this is a new game run, if it is, clear the log file and write into it
    if(empty){
        //write into log file
        ofstream logFile("gamelog.txt", std::ios::trunc);
        logFile << il->stringToLog() << endl;
        logFile.close();
        empty = false;
    }
    else{
        //write into log file
        ofstream logFile("gamelog.txt", std::ios::app);
        logFile << il->stringToLog() << endl;
        logFile.close();
    }
}

//Class Subject
//Subject constructor
Subject::Subject(){
}

//Subject destructor
Subject::~Subject(){ 
    // delete this->_observer;
}

//Subject assignment operator
Subject& Subject::operator=(const Subject& s1){
    return *this;
}

//Subject insertion stream
std::ostream& operator<<(std::ostream &strm, const Subject &s1){
    return strm;
}

//Subject copy constructor
Subject::Subject(const Subject& s){
}

//Subject's notify() method
void Subject::notify(ILoggable* il){
    LogObserver* observer = new LogObserver();
    observer->update(il);
}

//Class ILoggable
//ILoggable constructor
ILoggable::ILoggable(){
}

//ILoggable destructor
ILoggable::~ILoggable(){
}

//ILoggable assignment operator
ILoggable& ILoggable::operator=(const ILoggable& il){
    return *this;
}

//ILoggable copy constructor
ILoggable::ILoggable(const ILoggable& il){
}

//ILoggable stream instertion
std::ostream& operator<<(std::ostream &strm, const ILoggable &il){
    return strm;
}