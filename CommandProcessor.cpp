


#include "CommandProcessor.h"
#include <iostream>
#include <vector>
#include<string>
using std::vector;
using std::string;


//constructor
CommandProcessor::CommandProcessor(){
    state="start";
    c=new Command();
    done=false;
}


//destructor
CommandProcessor::~CommandProcessor(){
    delete c;
}

//validates the user's commands and if invalid saves the error message to a vector of strings
bool CommandProcessor::validate(string command){

    if(state=="start")
    {
        if(command=="loadmap")
            return true;
        else
            c->effect.push_back(new string("invalid command, the valid command is loadmap."));
        return false;
    }
    else
    if(state=="maploaded")
    {
        if(command=="loadmap")
            return true;
        else
        if(command=="validatemap")
            return true;
        else
            c->effect.push_back(new string("invalid command, valid commands are loadmap or validatemap."));
        return false;
    }
    else
    if(state=="mapvalidated"){
        if(command=="addplayer")
            return true;
        else
            c->effect.push_back(new string("invalid command, the valid command is addplayer."));
        return false;
    }
    else
    if(state=="playersadded"){
        if(command=="addplayer")
            return true;
       
        if(command=="gamestart")
            return true;
       else
        c->effect.push_back(new string("invalid command, valid commands are addplayer or gamestart."));
        return false;
    }
    else
    if(state=="win")
    {
        if(command=="quit")
            return true;
        else
        if(command=="replay")
            return true;
        else
            c->effect.push_back(new string("invalid command, valid commands are quit or replay."));
        return false;
    }
    else
        return false;
}

//this method saves the command
void CommandProcessor::saveCommand(string command){

    c->command.push_back(new string(command));

}

//handles the user's commands and passes through the stages of the game
void CommandProcessor::playegame(string line)
{
    if (state == "start") {
        // State: start
        // valid inputs: loadmap
        if (line == "loadmap") {
            //loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = "maploaded";
        } else {
            cout << "Invalid command. Valid commands: loadmap" << endl;
        }
    } else if (state == "maploaded") {
        // State: map loaded
        // Valid inputs: loadmap, validatemap
        if (line == "loadmap") {
            //loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = "maploaded";
        } else if (line == "validatemap") {
            //validateMap();
            cout << "Map now validated, you are in validated state. Valid input: addplayer" << endl;
            state = "mapvalidated";
        }
        else{
            cout<<"Invalid command. Valid commands: loadmap, validatemap."<<endl;
        }
    } else if (state == "mapvalidated") {
        // State: map validated
        // Valid input: addplayer
        if (line == "addplayer") {
            // addPlayers();
            cout<<"you are now in players added state. Valid input: addplayer, gamestart."<<endl;

            state = "playersadded";

        }
        else {
            cout << "Invalid command. Valid command: addplayer." << endl;
        }
    }
        //players added state
    else if(state=="playersadded"){
        //state: players added
        //valid input: addplayer, assigncountries
        if(line=="addplayer")
        {
            //addPlayers();
            cout<<"you are now in players added state. Valid input: addplayer, gamestart."<<endl;

            state = "playersadded";
        }
        else
        if(line=="gamestart")
        {
            //assignReinforcement();
            cout<<"starting the game... Valid input: replay, quit."<<endl;

            //here game should be played automatically
            //then jump to state win
            state="win";

        }
        else
            cout<<"Invalid command. Valid commands: addplayer, gamestart."<<endl;
    }
    else
    
    if(state=="win"){
       
        if(line=="replay"){

startMessage();
            state="start";
        }
        else
        if(line=="quit")
        {
            cout<<"game ended."<<endl;
            done=true;
        }
        else
            cout<<"invalid command, valid commands are replay, quit."<<endl;


    }
}

//read's user's commands, saves and validates them
void CommandProcessor:: readCommand(){
    bool valid;
    string yourCommand;
    cin>>yourCommand;
    saveCommand(yourCommand);
  valid= validate(yourCommand);
    {
        //this will handle the user's input to pass through stages of the game
        playegame(yourCommand);
    }


}

//keeps on taking user's command until the end of game
void CommandProcessor::start(){
    startMessage();
    while(done==false)
    {
        readCommand();
    }
    
}

//prints out a start message
void CommandProcessor::startMessage()
{
     cout << "Now in start state. Valid input: loadmap" << endl;
}


//returns a vector of strings which are the commands that the user entered
vector<string*> CommandProcessor::getCommand(){
    return c->command;
}
