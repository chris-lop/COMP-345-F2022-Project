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
   FileLineReader* f;
   void readCommand();
    public:
    //constructor
    FileCommandProcessorAdapter();
    //destructor
    ~FileCommandProcessorAdapter();
    
    
    
};
#endif
