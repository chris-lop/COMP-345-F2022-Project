
#include "Command.h"
#include <string>
#include <iostream>
using std::string;
using std::endl;


//constructors
Command::Command(){
   
    this->command={};
    this->effect={};
}

Command::Command(string command, string effect){
    this->command=command;
    this->effect=effect;
}

//destructor
Command::~Command(){

}


//stream operators
std::ostream& operator<<(std::ostream &strm, const Command &c){
    strm << "The  command and its effect are " << c.command <<" and " <<  c.effect << endl;
    return strm;

}

Command::Command(const Command& c1){
    this->command = c1.command;
    this->effect = c1.effect;
}

Command& Command::operator=(const Command& c1){
	this->command = c1.command;
    this->effect = c1.effect;
	return *this;
}

string Command::getCommand(){
    return this->command;
}

string Command::getEffect(){
    return this->effect;
}


//saves effect of the command to the vector of strings
void Command::saveEffect(string eff){
    this->effect = eff;
}
