
#include "CommandProcessor.h"
#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;

// constructor
CommandProcessor::CommandProcessor()
{
    state = "start";
    vector<Command*> commands;
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

CommandProcessor::CommandProcessor(const CommandProcessor& cp){
  commands = vector<Command*>();
    for (Command* c: cp.commands) {
        commands.push_back(new Command(*c));
    }    
    this->state = cp.state;
    this->done = cp.done;
    this->valid = cp.valid;
}

CommandProcessor& CommandProcessor::operator=(const CommandProcessor& cp){
	commands = vector<Command*>();
    for (Command* c: cp.commands) {
        commands.push_back(new Command(*c));
    } 
    this->state = cp.state;
    this->done = cp.done;
    this->valid = cp.valid;
	return *this;
}


// validates the user's commands and if invalid saves the error message to a vector of strings
// returns a string of the effect resulting from the command passed to it
string CommandProcessor::validate(Command* c)
{
    string command = c->getCommand();

    if (state == "start")
    {
        if (command.find("loadmap")==0)
        {
            c->saveEffect("Now in map loaded state. Valid input: loadmap<mapfile>, validatemap.");
            return "Now in map loaded state. Valid input: loadmap<mapfile>, validatemap.";
        }
        else
        {
            c->saveEffect("invalid command, the valid command is loadmap<mapfile>.");
            return "invalid command, the valid command is loadmap<mapfile>.";
        }
    }
    else if (state == "maploaded")
    {
        if (command.find("loadmap")==0)
        {
            c->saveEffect("Now in map loaded state. Valid input: loadmap<mapfile>, validatemap.");        
            return "Now in map loaded state. Valid input: loadmap<mapfile>, validatemap.";
        }
        else if (command == "validatemap")
        {
            c->saveEffect("Map now validated, you are in validated state. Valid input: addplayer<playername>.");
            return "Map now validated, you are in validated state. Valid input: addplayer<playername>.";
        }
        else
        {
            c->saveEffect("invalid command, valid commands are loadmap<mapfile>, validatemap.");
            return "invalid command, valid commands are loadmap<mapfile>, validatemap.";
        }
    }
    else if (state == "mapvalidated")
    {
        if (command.find("addplayer") == 0)
        {
            c->saveEffect("you are now in players added state. Valid input: addplayer<playername>, gamestart.");
            return "you are now in players added state. Valid input: addplayer<playername>, gamestart.";
        }
        else
        {
            c->saveEffect("invalid command, the valid command is addplayer<playername>.");
            return "invalid command, the valid command is addplayer<playername>.";
        }
    }
    else if (state == "playersadded")
    {
        if (command.find("addplayer") == 0)
        {
            c->saveEffect("you are now in players added state. Valid input: addplayer<playername>, gamestart.");
            return "you are now in players added state. Valid input: addplayer<playername>, gamestart.";
        }

        if (command == "gamestart")
        {
            c->saveEffect("starting the game... Valid input: replay, quit.");
            return "starting the game... Valid input: replay, quit.";
        }
        else
        {
            c->saveEffect("invalid command, valid commands are addplayer<playername>, gamestart.");
            return "invalid command, valid commands are addplayer<playername>, gamestart.";
        }
    }
    else if (state == "win")
    {
        if (command == "quit")
        {
            c->saveEffect("game ended.");
            return "game ended.";
        }
        else if (command == "replay")
        {
            c->saveEffect("Now in start state. Valid input: loadmap<mapfile>");
            return "Now in start state. Valid input: loadmap<mapfile>";
        }
        else
        {
            c->saveEffect("invalid command, valid commands are quit or replay.");
            return "invalid command, valid commands are quit or replay.";
        }
    }
    else{
        c->saveEffect("invalid command, no state.");
        return "invalid command, no state.";
    }
}

// this method saves the command
void CommandProcessor::saveCommand(Command* command)
{
    this->commands.push_back(command);
}

// read's user's commands, saves and validates them, then saves the effects of the commands
Command* CommandProcessor::readCommand()
{
    string yourCommand;
    cin >> yourCommand;
    Command* c = new Command(yourCommand, "");
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

vector<Command*> CommandProcessor::getterCommands(){
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
        getCommand();
    }
}

// prints out a start message
void CommandProcessor::startMessage()
{
    cout << "Now in start state. Valid input: loadmap<mapfile>" << endl;
}

// returns a vector of strings which are the commands that the user entered
Command* CommandProcessor::getCommand()
{
    Command* c = new Command(*readCommand());
    saveCommand(c);
    return c;
}

// handles the user's commands and passes through the stages of the game
bool CommandProcessor::playegame(Command* command)
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

