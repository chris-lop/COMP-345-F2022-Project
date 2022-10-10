
#include <iostream>
#include "GameEngine.h"
#include <string>
using std::cin; using std::cout; using std::string; using std::endl;

void testGameStates() {
    //creates a pointer to a GameEngine object
    GameEngine *engine = new GameEngine(); 
    //prints out the start message
    engine->startMessage(); 
    //keeps on taking user input as long as the final state has not been reached
    while (!engine->finished()) { 
        string line;
        cin>>line;
        //passes input to the handleInput(string) method to pass through the phases depending on the user's input
        engine->handleInput(line); 
    }
   
}

