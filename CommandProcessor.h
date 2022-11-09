

#include "Command.h"
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CommandProcessor
{
private:
    Command *c;
    string state;
    // declared virtual so that inheritance applies to it
    virtual void readCommand();
    bool done;

public:
    vector<string *> getCommand();
    void start();
    void startMessage();
    bool playegame(string line);
    bool validate(string command);
    void saveCommand(string command);
    CommandProcessor();
    virtual ~CommandProcessor();
};
#endif
