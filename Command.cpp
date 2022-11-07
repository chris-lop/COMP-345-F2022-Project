#include "Command.h"
#include <string>
#include <iostream>
using namespace std;
using std::vector;
using std::string;


//default constructor
Command::Command(){
   
    this->command={};
    this->effect={};
}

//parametrized constructor
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


//output stream operator
std::ostream& operator<<(std::ostream &strm, const Command &c){
 strm<<"the saved effects are:"<<std::endl;
   for(string* s:c.effect){
        strm<<*(s)<<endl;
    }
   
    return strm;

}



//saves effect of the command to the vector of strings
void Command::saveEffect(string eff){

    effect.push_back(new string(eff));
}
