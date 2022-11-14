#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LoggingObserver.h"
using std::string;
using std::vector;

// class forward declarations
class ILoggable;
class Subject;
class CommandProcessor;
class Command;

// free functions
void testCommandProcessor(string command);

class Command : public ILoggable, public Subject
{
public:
  // attributes
  string command;
  string effect;

  // private method that saves the effect of the command object
  void saveEffect(string effect);

  // constructors
  Command(string command, string effect);

  // default constructor
  Command();

  // destructor
  ~Command();

  // copy constructor
  Command(const Command &c1);

  // assignment operator
  Command &operator=(const Command &c1);

  // getters
  string getCommand();
  string getEffect();

  // stream insertion operator
  friend std::ostream &operator<<(std::ostream &strm, const Command &c);

  // ILoggable method
  string stringToLog();
};

class CommandProcessor : public ILoggable, public Subject
{
private:
  // attributes
  vector<Command *> commands;
  string state;
  bool done;
  bool valid;

  // declared virtual so that inheritance applies to it
  virtual Command *readCommand();

public:
  // returns a pointer to a command object
  Command *getCommand();
  void start();
  void startMessage();
  bool playegame(Command *command);

  // getters
  bool getvalid();
  vector<Command *> getterCommands();
  string get_state();

  // copy constructor
  CommandProcessor(const CommandProcessor &cp);

  // assignment operator
  CommandProcessor &operator=(const CommandProcessor &cp);

  // stream insertion operator
  friend std::ostream &operator<<(std::ostream &strm, const CommandProcessor &cp);

  // setters
  void set_state(string line);
  bool validate(Command *c);
  void saveCommand(Command *command);

  // constructor
  CommandProcessor();

  // destructor
  virtual ~CommandProcessor();

  // ILoggable method
  string stringToLog();
};

class FileLineReader
{
public:
  // this method reads commands from a file and returns them in a vector of strings
  vector<string *> readLineFromFile(string fname);
};

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
  // attributes
  string f_name;
  FileLineReader *f;
  int lineNum;

  // overridden inherited method from CommandProcessor
  Command *readCommand();

public:
  // constructor
  FileCommandProcessorAdapter();

  // copy constructor
  FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcp);

  // assignment operator
  FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &fcp);

  // stream insertion operator
  friend std::ostream &operator<<(std::ostream &strm, const FileCommandProcessorAdapter &fcp);

  // destructor
  ~FileCommandProcessorAdapter();

  // setter
  void set_f_name(string name);
};
