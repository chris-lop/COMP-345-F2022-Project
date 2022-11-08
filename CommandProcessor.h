
#include "Command.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CommandProcessor{
private:
    Command* c;
    string state;
    void readCommand();
    bool done;

public:
void start();
void startMessage();
    void playegame(string line);
    bool validate(string command);
    void saveCommand(string command);
    vector<string*> getCommand();
    
    //constructor
    CommandProcessor();
    
    //destructor
    ~CommandProcessor();
};
