
#include "Command.h"
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"
using namespace std;

class ILoggable;
class Subject;
class CommandProcessor;
class Command;

class CommandProcessor : public ILoggable, public Subject
{
private:
    Command *c;
    string state;
    // declared virtual so that inheritance applies to it
    virtual void readCommand();
    bool done;
    bool valid;

public:
    vector<string *> getCommand();
    void start();
    void startMessage();
    bool playegame(string line);
    // getters
    Command *get_c();
    bool getvalid();
    string get_state();

    // setter
    void set_state(string line);

    string validate(string command);
    void saveCommand(string command);
    CommandProcessor();
    virtual ~CommandProcessor();
    // ILoggable method
    std::string stringToLog();
};
#endif
