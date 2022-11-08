#include <iostream>
#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include<string>
using std::vector;
using std::string;
class Command{
public:
    std::vector <string*> command;
    std::vector<string*> effect;

    void saveEffect(string effect);

    //constructors
    Command(std::vector<string*> command, std::vector<string*> effect);

    //default constructor
    Command();

    //destructor
    ~Command();

   
    friend std::ostream& operator << (std::ostream& strm, const Command& c);
   
 

};
#endif
