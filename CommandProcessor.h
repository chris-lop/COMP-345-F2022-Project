
#include "Command.h"
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CommandProcessor{
private:
    Command* c;
    string state;
    //declared virtual so that inheritance applies to it
    virtual void readCommand();
    bool done;
    bool valid;

public:
vector<string*> getCommand();
void start();
void startMessage();
//getters
Command* get_c();
bool getvalid();

    void playegame(string line);
    string validate(string command);
    void saveCommand(string command);
    CommandProcessor();
    virtual ~CommandProcessor();
};
#endif
