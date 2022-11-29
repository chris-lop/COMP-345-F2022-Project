#include "CommandProcessor.h"
#include "LoggingObserver.h"
#include "GameEngine.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// ----Command Class ---------

// constructors
Command::Command()
{
    this->command = {};
    this->effect = {};
   
}

Command::Command(string command, string effect)
{
    this->command = command;
    this->effect = effect;
}

// destructor
Command::~Command()
{
}

// stream operators
std::ostream &operator<<(std::ostream &strm, const Command &c)
{
    strm << "The  command and its effect are " << c.command << " and " << c.effect << endl;
    return strm;
}

//copy constructor
Command::Command(const Command &c1)
{
    this->command = c1.command;
    this->effect = c1.effect;
}

//assignment operator
Command &Command::operator=(const Command &c1)
{
    this->command = c1.command;
    this->effect = c1.effect;
    return *this;
}


//getters
string Command::getCommand()
{
    return this->command;
}

string Command::getEffect()
{
    return this->effect;
}

// saves effect of the command to the vector of strings
void Command::saveEffect(string eff)
{
    this->effect = eff;
    notify(this);
}

// Method providing the string to log
string Command::stringToLog()
{
    string s = "The effect saved is ";
    return (s).append(this->effect).append(" from the command ").append(this->command);
}

// ----CommandProcessor Class ---------

// constructor
CommandProcessor::CommandProcessor()
{
   
    vector<Command *> commands;
    this->commands = commands;
    valid = false;
    g=new GameEngine();
}

// destructor
CommandProcessor::~CommandProcessor()
{
    for (int i = 0; i < this->commands.size(); i++)
    {
        delete this->commands.at(i);
    }
}

//copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor &cp)
{
    commands = vector<Command *>();
    for (Command *c : cp.commands)
    {
        commands.push_back(new Command(*c));
    }
    
 this->g = new GameEngine(*cp.g);
    this->valid = cp.valid;
}

//assignment operator
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &cp)
{
    commands = vector<Command *>();
    for (Command *c : cp.commands)
    {
        commands.push_back(new Command(*c));
    }
  this->g = new GameEngine(*cp.g);
    this->valid = cp.valid;
    return *this;
}

//stream insertion operator
std::ostream &operator<<(std::ostream &strm, const CommandProcessor &cp)
{
   strm<<"The commands are: "<<endl;
  for(Command* c:cp.commands)
  strm<<*c;
  return strm;
}


// validates the user's commands and then saves the effect that it results in
bool CommandProcessor::validate(Command *c)
{
    string command = c->getCommand();

    if (g->getState() == "start")
    {
        if (command.find("loadmap") == 0)
        {
            c->saveEffect("in map loaded state");
            return true;
        }
        else
        {
            c->saveEffect("invalid command");
            return false;
        }
    }
    else if (g->getState() == "maploaded")
    {
        if (command.find("loadmap") == 0)
        {
            c->saveEffect("in map loaded state");
            return true;
        }
        else if (command == "validatemap")
        {
            c->saveEffect("in validated state");
            return true;
        }
        else
        {
            c->saveEffect("invalid command");
            return false;
        }
    }
    else if (g->getState() == "mapvalidated")
    {
        if (command.find("addplayer") == 0)
        {
            c->saveEffect("in players added state");
            return true;
        }
        else
        {
            c->saveEffect("invalid command");
            return false;
        }
    }
    else if (g->getState() == "playersadded")
    {
        if (command.find("addplayer") == 0)
        {
            c->saveEffect("in players added state");
            return true;
        }

        if (command == "gamestart")
        {
            c->saveEffect("in game start state");
            return true;
        }
        else
        {
            c->saveEffect("invalid command");
            return false;
        }
    }
    else if (g->getState() == "win")
    {
        if (command == "quit")
        {
            c->saveEffect("in game ended state");
            return true;
        }
        else if (command == "replay")
        {
            c->saveEffect("in start state");
            return true;
        }
        else
        {
            c->saveEffect("invalid command");
            return false;
        }
    }
    else
    {
        c->saveEffect("invalid command");
        return false;
    }
}

// this method saves the command object to the vector of commands
void CommandProcessor::saveCommand(Command *command)
{
    this->commands.push_back(command);
    notify(this);
}

// read's user's commands as strings and then creates command object and returns it
Command *CommandProcessor::readCommand()
{
    string yourCommand;
    getline(cin, yourCommand);
    Command *c = new Command(yourCommand, "");
    return c;
}

//getters
bool CommandProcessor::getvalid()
{
    return this->valid;
}



vector<Command *> CommandProcessor::getterCommands()
{
    return this->commands;
}



// keeps on taking user's command until the end of game
void CommandProcessor::start()
{
    g->startMessage();
    while (g->getDone() == false)
    {
       Command* command=getCommand();
        validate(command);
        g->playegame(command);
    }
}

// prints out a start message
void CommandProcessor::startMessage()
{
    cout << "Now in start state. Valid input: loadmap<mapfile>" << endl;
}

// creates command object, saves and returns a pointer to it
Command *CommandProcessor::getCommand()
{
    Command *c = new Command(*readCommand());
    saveCommand(c);
    return c;
}

//------ FileLineReader Class ------

// returns a string of the commands read from the file
vector<string *> FileLineReader::readLineFromFile(string fname)
{
    string text;
    vector<string *> co = {};
    ifstream readFile(fname);
    while (getline(readFile, text))
    {

        // reads text from the file and saves it to a string of commands
        co.push_back(new string(text));
    }

    readFile.close();
    return co;
}

// Method providing the string to log
string CommandProcessor::stringToLog()
{
    string str = "";
    string s = "The command and its effect saved are ";
    str.append(s).append(commands.at(commands.size() - 1)->command).append(" and ").append(commands.at(commands.size() - 1)->effect);

    return str;
}

//-------FileCommandProcessorAdapter Class------

// constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() : CommandProcessor(), f_name(""), f(new FileLineReader()), lineNum(0)
{
}

//copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcp)
{
    f=new FileLineReader();
    *f=*fcp.f;
    this->f_name = fcp.f_name;
    this->lineNum = fcp.lineNum;
    
}

//assignment operator
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &fcp)
{
   f=new FileLineReader();
   *f=*fcp.f;
    this->f_name = fcp.f_name;
    this->lineNum = fcp.lineNum;
    return *this;
}

//stream insertion operator
std::ostream &operator<<(std::ostream &strm, const FileCommandProcessorAdapter &fcp)
{
   strm<<"The name of the file and the line number are: "<<fcp.f_name<<", "<<fcp.lineNum<<endl;
  return strm;
}

// destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete f;
}

// setter
void FileCommandProcessorAdapter::set_f_name(string name)
{
    f_name = name;
}

// overriding the readCommand() method from the base class
Command *FileCommandProcessorAdapter::readCommand()
{
    // read the commands from a file
    vector<string *> commands = f->readLineFromFile(f_name);
    string command = *commands.at(lineNum);
    lineNum = lineNum + 1;
    Command *c = new Command(command, "");
    return c;
}

