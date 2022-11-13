#include <iostream>
#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include<string>
#include "LoggingObserver.h"
using std::string;

// class ILoggable;
// class Subject;
// class Command;

class Command {
public:
    string command;
    string effect;

    void saveEffect(string effect);

    //constructors
    Command(string command, string effect);

    //default constructor
    Command();

    //destructor
    ~Command();

    Command(const Command& c1);
    Command& operator=(const Command& c1);

    //getters
    string getCommand();
    string getEffect();

   
    friend std::ostream& operator << (std::ostream& strm, const Command& c);

    // ILoggable method
    // std::string stringToLog();

};
#endif
