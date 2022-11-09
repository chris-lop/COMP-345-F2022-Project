




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
    valid=false;
}


//destructor
CommandProcessor::~CommandProcessor(){
    delete c;
}

//validates the user's commands and if invalid saves the error message to a vector of strings
//returns a string of the effect resulting from the command passed to it
string CommandProcessor::validate(string command){

    if(state=="start")
    {
        if(command.substr(0,8)=="loadmap<"&&command.substr(command.length()-1)==">")
        {
            valid=true;
            return "Now in map loaded state. Valid input: loadmap<mapfile>, validatemap.";
            
        }
        else
        {
            valid=false;
            c->effect.push_back(new string("invalid command, the valid command is loadmap<mapfile>."));
        return "invalid command, the valid command is loadmap<mapfile>.";
        }
    }
    else
    if(state=="maploaded")
    {
        if(command.substr(0,8)=="loadmap<"&&command.substr(command.length()-1)==">")
        {
            valid=true;
            return "Now in map loaded state. Valid input: loadmap<mapfile>, validatemap.";
        }
        else
        if(command=="validatemap")
        {
            valid=true;
            return "Map now validated, you are in validated state. Valid input: addplayer<playername>.";
        }
        else
        {
            valid=false;
            c->effect.push_back(new string("invalid command, valid commands are loadmap<mapfile>, validatemap."));
        return "invalid command, valid commands are loadmap<mapfile>, validatemap.";
        }
    }
    else
    if(state=="mapvalidated"){
        if(command.substr(0,10)=="addplayer<"&&command.substr(command.length()-1)==">")
        {
            valid=true;
            return "you are now in players added state. Valid input: addplayer<playername>, gamestart.";
        }
        else
        {
            valid=false;
            c->effect.push_back(new string("invalid command, the valid command is addplayer<playername>."));
        return "invalid command, the valid command is addplayer<playername>.";
        }
    }
    else
    if(state=="playersadded"){
        if(command.substr(0,10)=="addplayer<"&&command.substr(command.length()-1)==">")
        {
            valid=true;
            return "you are now in players added state. Valid input: addplayer<playername>, gamestart.";
        }
       
        if(command=="gamestart")
        {
            valid=true;
            return "starting the game... Valid input: replay, quit.";
        }
       else
       {
           valid=false;
        c->effect.push_back(new string("invalid command, valid commands are addplayer<playername>, gamestart."));
        return "invalid command, valid commands are addplayer<playername>, gamestart.";
       }
    }
    else
    if(state=="win")
    {
        if(command=="quit")
        {
            valid=true;
            return "game ended.";
        }
        else
        if(command=="replay")
        {
            valid=true;
            return "Now in start state. Valid input: loadmap<mapfile>";
        }
        else
        {
            valid=false;
            c->effect.push_back(new string("invalid command, valid commands are quit or replay."));
        return "invalid command, valid commands are quit or replay.";
        }
    }
    else
        return "";
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
        // valid inputs: loadmap<mapfile>
        if (line.substr(0,8) == "loadmap<"&&line.substr(line.length()-1)==">") {
            //loadMap();
            cout << "Now in map loaded state. Valid input: loadmap<mapfile>, validatemap" << endl;
            state = "maploaded";
        } else {
            cout << "Invalid command. Valid commands: loadmap<mapfile>" << endl;
        }
    } else if (state == "maploaded") {
        // State: map loaded
        // Valid inputs: loadmap<mapfile>, validatemap
        if (line.substr(0,8) == "loadmap<"&& line.substr(line.length()-1)==">") {
           
            cout << "Now in map loaded state. Valid input: loadmap<mapfile>, validatemap" << endl;
            state = "maploaded";
        } else if (line == "validatemap") {
         
            cout << "Map now validated, you are in validated state. Valid input: addplayer<playername>." << endl;
            state = "mapvalidated";
        }
        else{
            cout<<"Invalid command. Valid commands: loadmap<mapfile>, validatemap."<<endl;
        }
    } else if (state == "mapvalidated") {
        // State: map validated
        // Valid input: addplayer<playername>
        if (line.substr(0,10) == "addplayer<"&&line.substr(line.length()-1)==">") {
            
            cout<<"you are now in players added state. Valid input: addplayer<playername>, gamestart."<<endl;

            state = "playersadded";

        }
        else {
            cout << "Invalid command. Valid command: addplayer<playername>." << endl;
        }
    }
        //players added state
    else if(state=="playersadded"){
        //state: players added
        //valid input: addplayer<playername>, assigncountries
        if(line.substr(0,10)=="addplayer<"&&line.substr(line.length()-1)==">")
        {
            
            cout<<"you are now in players added state. Valid input: addplayer<playername>, gamestart."<<endl;

            state = "playersadded";
        }
        else
        if(line=="gamestart")
        {
           
            cout<<"starting the game... Valid input: replay, quit."<<endl;

            //here game should be played automatically
            cout<<"assigning reinforcement."<<endl;
            cout<<"issuing orders."<<endl;
            cout<<"executing orders."<<endl;
           cout<<"enter replay or quit."<<endl;
            //then jump to state win
            state="win";

        }
        else
            cout<<"Invalid command. Valid commands: addplayer<playername>, gamestart."<<endl;
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

//read's user's commands, saves and validates them, then saves the effects of the commands
void CommandProcessor:: readCommand(){
    string ycommand;
    string yourCommand;
    cin>>yourCommand;
    saveCommand(yourCommand);
    //validates the command which will return a string of the effect and save invalid commands' effects
  ycommand= validate(yourCommand);
  //saves the effect of the command if the command is valid 
  if(valid==true)
  c->saveEffect(ycommand);
  
    {
        //this will handle the user's input to pass through stages of the game
        playegame(yourCommand);
    }


}

//getters
Command* CommandProcessor::get_c(){
    return c;
}


bool CommandProcessor::getvalid(){
    return valid;
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
     cout << "Now in start state. Valid input: loadmap<mapfile>" << endl;
}


//returns a vector of strings which are the commands that the user entered
vector<string*> CommandProcessor::getCommand(){
    return c->command;
}
