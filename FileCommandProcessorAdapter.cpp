
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
     bool valid;
   //read the commands from a file
   vector<string*> commands=f->readLineFromFile(f_name);
   for(int i=0;i<commands.size();i++){
       saveCommand(*(commands.at(i)));
       valid=validate(*(commands.at(i)));
       playegame(*(commands.at(i)));
   }
    
}
