
#include "CommandProcessor.h"
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include "FileLineReader.h"
#include "FileCommandProcessorAdapter.h"


//constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter():CommandProcessor(),f_name(""),f(new FileLineReader()){
    
}

//destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete f;
    
}

//setter
void FileCommandProcessorAdapter::set_f_name(string name){
    f_name=name;
}

//overriding the readCommand() method from the base class
void FileCommandProcessorAdapter:: readCommand(){
     string ycommand;
   //read the commands from a file
   vector<string*> commands=f->readLineFromFile(f_name);
   for(int i=0;i<commands.size();i++){
       //saves the command
       saveCommand(*(commands.at(i)));
       //validate will save effect of invalid commands and return a string of the effect whether valid or invalid
       ycommand=validate(*(commands.at(i)));
       //saves the effect of the command if the command is valid
       if(getvalid()==true){
      get_c()->saveEffect(ycommand);
       }
       playegame(*(commands.at(i)));
   }
    
}
