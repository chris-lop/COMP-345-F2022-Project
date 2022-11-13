#include "CommandProcessor.h"
#include "FileLineReader.h"
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#ifndef FILECOMMANDPROCESSORADAPTER_H
#define FILECOMMANDPROCESSORADAPTER_H


class FileCommandProcessorAdapter: public CommandProcessor{
private:
  string f_name;
  FileLineReader* f;
  Command* readCommand();
  int lineNum;
public:
    //constructor
    FileCommandProcessorAdapter();
    //destructor
    ~FileCommandProcessorAdapter();
   
   //setter
     void set_f_name(string name);
    
    
};
#endif
