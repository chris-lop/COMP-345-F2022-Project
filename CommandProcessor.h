
#include "Command.h"
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include <iostream>
#include <string>
#include <vector>
// #include "LoggingObserver.h"
using namespace std;

class ILoggable;
class Subject;
class CommandProcessor;
class Command;

void testCommandProcessor();

class CommandProcessor //: public ILoggable, public Subject
{
private:
    vector <Command*> commands;
    string state;
    // declared virtual so that inheritance applies to it
    bool done;
    bool valid;

public:
    virtual Command readCommand();

   Command getCommand();
    void start();
    void startMessage();
    bool playegame(Command* command);
    // getters
    bool getvalid();
    vector<Command*> getterCommands();
    string get_state();


    CommandProcessor(const CommandProcessor& cp);
    CommandProcessor& operator=(const CommandProcessor& cp);

    // setter
    void set_state(string line);

    string validate(Command* c);
    void saveCommand(Command* command);
    CommandProcessor();
    virtual ~CommandProcessor();
    // ILoggable method
    // std::string stringToLog();
};
#endif
