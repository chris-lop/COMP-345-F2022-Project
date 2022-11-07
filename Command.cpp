#include "Command.h"
#include <string>
#include <iostream>
using namespace std;
using std::vector;
using std::string;


//constructors
Command::Command(){
   
    this->command={};
    this->effect={};
}

Command::Command(std::vector<string*>command, std::vector<string*> effect){
    this->command=command;
    this->effect=effect;
}

//destructor
Command::~Command(){
for(string* s:effect){
delete(s);
}
for(string* c:command){
    delete(c);
}

}

//stream operators



std::ostream& operator<<(std::ostream &strm, const Command &c){
 strm<<"the saved effects are:"<<std::endl;
   for (string* e: c.effect){
        strm<<e;
    }
    return strm;

}



//saves effect of the command to the vector of strings
void Command::saveEffect(string eff){

    effect.push_back(new string(eff));
}
