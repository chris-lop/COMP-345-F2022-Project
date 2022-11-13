#pragma once

#include "CommandProcessor.h"
#include "LoggingObserver.h"
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

Command::Command(const Command &c1)
{
    this->command = c1.command;
    this->effect = c1.effect;
}

Command &Command::operator=(const Command &c1)
{
    this->command = c1.command;
    this->effect = c1.effect;
    return *this;
}

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

string Command::stringToLog()
{
    string s = "The effect saved is ";
    return (s).append(this->effect).append(" from the command ").append(this->command);
}

// ----CommandProcessor Class ---------

// constructor
CommandProcessor::CommandProcessor()
{
    state = "start";
    vector<Command *> commands;
    this->commands = commands;
    done = false;
    valid = false;
}

// destructor
CommandProcessor::~CommandProcessor()
{
    for (int i = 0; i < this->commands.size(); i++)
    {
        delete this->commands.at(i);
    }
}

CommandProcessor::CommandProcessor(const CommandProcessor &cp)
{
    commands = vector<Command *>();
    for (Command *c : cp.commands)
    {
        commands.push_back(new Command(*c));
    }
    this->state = cp.state;
    this->done = cp.done;
    this->valid = cp.valid;
}

CommandProcessor &CommandProcessor::operator=(const CommandProcessor &cp)
{
    commands = vector<Command *>();
    for (Command *c : cp.commands)
    {
        commands.push_back(new Command(*c));
    }
    this->state = cp.state;
    this->done = cp.done;
    this->valid = cp.valid;
    return *this;
}

// validates the user's commands and if invalid saves the error message to a vector of strings
// returns a string of the effect resulting from the command passed to it
bool CommandProcessor::validate(Command *c)
{
    string command = c->getCommand();

    if (state == "start")
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
    else if (state == "maploaded")
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
    else if (state == "mapvalidated")
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
    else if (state == "playersadded")
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
    else if (state == "win")
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

// this method saves the command
void CommandProcessor::saveCommand(Command *command)
{
    this->commands.push_back(command);
    notify(this);
}

// read's user's commands, saves and validates them, then saves the effects of the commands
Command *CommandProcessor::readCommand()
{
    string yourCommand;
    getline(cin, yourCommand);
    Command *c = new Command(yourCommand, "");
    return c;
}

bool CommandProcessor::getvalid()
{
    return this->valid;
}

string CommandProcessor::get_state()
{
    return this->state;
}

vector<Command *> CommandProcessor::getterCommands()
{
    return this->commands;
}

// setter
void CommandProcessor::set_state(string line)
{
    this->state = line;
}

// keeps on taking user's command until the end of game
void CommandProcessor::start()
{
    startMessage();
    while (done == false)
    {
        playegame(getCommand());
    }
}

// prints out a start message
void CommandProcessor::startMessage()
{
    cout << "Now in start state. Valid input: loadmap<mapfile>" << endl;
}

// returns a vector of strings which are the commands that the user entered
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

// handles the user's commands and passes through the stages of the game
bool CommandProcessor::playegame(Command *command)
{
    validate(command);
    if (state == "start")
    {
        // State: start
        // valid inputs: loadmap
        if ((command->getCommand()).find("loadmap") == 0)
        {
            // loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = "maploaded";
            return true;
        }
        else
        {
            cout << "Invalid command. Valid commands: loadmap" << endl;
            return false;
        }
    }
    else if (state == "maploaded")
    {
        // State: map loaded
        // Valid inputs: loadmap, validatemap
        if ((command->getCommand()).find("loadmap") == 0)
        {
            // loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = "maploaded";
            return true;
        }
        else if (command->getCommand() == "validatemap")
        {
            // validateMap();
            cout << "Map now validated, you are in validated state. Valid input: addplayer" << endl;
            state = "mapvalidated";
            return true;
        }
        else
        {
            cout << "Invalid command. Valid commands: loadmap, validatemap." << endl;
            return false;
        }
    }
    else if (state == "mapvalidated")
    {
        // State: map validated
        // Valid input: addplayer
        if ((command->getCommand()).find("addplayer") == 0)
        {
            // addPlayers();
            cout << "you are now in players added state. Valid input: addplayer, gamestart." << endl;

            state = "playersadded";
            return true;
        }
        else
        {
            cout << "Invalid command. Valid command: addplayer." << endl;
            return false;
        }
    }
    // players added state
    else if (state == "playersadded")
    {
        // state: players added
        // valid input: addplayer, assigncountries
        if ((command->getCommand()).find("addplayer") == 0)
        {
            // addPlayers();
            cout << "you are now in players added state. Valid input: addplayer, gamestart." << endl;

            state = "playersadded";
            return true;
        }
        else if (command->getCommand() == "gamestart")
        {

            cout << "starting the game... Valid input: replay, quit." << endl;

            // here game should be played automatically
            cout << "assigning reinforcement." << endl;
            cout << "issuing orders." << endl;
            cout << "executing orders." << endl;
            cout << "enter replay or quit." << endl;
            // then jump to state win
            state = "win";

            // here game should be played automatically
            // then jump to state win
            state = "win";
            return true;
        }
        else
            cout << "Invalid command. Valid commands: addplayer, gamestart." << endl;
        return false;
    }
    else

        if (state == "win")
    {

        if (command->getCommand() == "replay")
        {

            startMessage();
            state = "start";
            return true;
        }
        else if (command->getCommand() == "quit")
        {
            cout << "game ended." << endl;
            done = true;
            return true;
        }
        else
            cout << "invalid command, valid commands are replay, quit." << endl;
        return false;
    }
    return true; // added by marc
}
