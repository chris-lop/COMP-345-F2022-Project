#pragma once

#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include "LoggingObserver.h"
using std::string;
using std::vector;

class ILoggable;
class Subject;
class CommandProcessor;
class Command;

void testCommandProcessor();

class Command : public ILoggable, public Subject
{
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
    string stringToLog();

};

class CommandProcessor : public ILoggable, public Subject
{
private:
    vector <Command*> commands;
    string state;
    // declared virtual so that inheritance applies to it
    bool done;
    bool valid;
    virtual Command* readCommand();
public:

   Command* getCommand();
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
    string stringToLog();
};

class FileLineReader{
    
  public:
  
  //this method reads commands from a file and returns them in a vector of strings
  vector<string*> readLineFromFile(string fname);

};


class FileCommandProcessorAdapter: public CommandProcessor{
private:
  string f_name;
  FileLineReader* f;
  Command* readCommand();
  int lineNum;
public:
    //constructor
    FileCommandProcessorAdapter();
    //destructor
    ~FileCommandProcessorAdapter();
   
   //setter
     void set_f_name(string name);
    
    
};
