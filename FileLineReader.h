#include <iostream>
#include "CommandProcessor.h"
#include<string>
#ifndef FILELINEREADER_H
#define FILELINEREADER_H
#include<vector>
#include<fstream>

class FileLineReader{
    
  public:
  
  //this method reads commands from a file and returns them in a vector of strings
  vector<string*> readLineFromFile(string fname);

};
#endif
