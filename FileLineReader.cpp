#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include"FileLineReader.h"
using std::vector;
using std::string;

//returns a string of the commands read from the file
vector<string*> FileLineReader::readLineFromFile(string fname){
    string text;
    vector<string*> co={};
    ifstream readFile(fname);
while (getline (readFile, text)) {
  
  // reads text from the file and saves it to a string of commands
   co.push_back(new string(text));
}

readFile.close();
return co;
    
}
