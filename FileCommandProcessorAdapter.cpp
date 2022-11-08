#include "CommandProcessor.h"
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include "FileLineReader.h"
#include "FileCommandProcessorAdapter.h"


//constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter():CommandProcessor(),f(new FileLineReader()){
    
}

//destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete f;
    
}

//overriding the readCommand() method from the base class
void FileCommandProcessorAdapter:: readCommand(){
      bool valid;
      string f_name;
   //read the commands from a file
   cout<<"enter the name of the file from which you want to read the commands."<<endl;
   cin>>f_name;
   vector<string*> commands=f->readLineFromFile(f_name);
   for(int i=0;i<commands.size();i++){
       saveCommand(*(commands.at(i)));
       valid=validate(*(commands.at(i)));
       playegame(*(commands.at(i)));
   }
    
}
