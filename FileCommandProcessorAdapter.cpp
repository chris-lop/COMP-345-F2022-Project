
#include "CommandProcessor.h"
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include "FileLineReader.h"
#include "FileCommandProcessorAdapter.h"


//constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter():CommandProcessor(),f_name(""),f(new FileLineReader()), lineNum(0){
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
Command* FileCommandProcessorAdapter:: readCommand(){
    //read the commands from a file
    vector<string*> commands=f->readLineFromFile(f_name);
    string command = *commands.at(lineNum);
    lineNum = lineNum + 1;
    Command* c = new Command(command, "");
    return c;
}
