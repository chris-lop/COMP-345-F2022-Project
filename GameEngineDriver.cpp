
#include <iostream>
#include "GameEngine.h"
#include <string>
using std::cin; using std::cout; using std::string; using std::endl;

void testGameStates() {
    GameEngine *engine = new GameEngine(); //creates a pointer to a GameEngine object
    engine->startMessage(); //prints out the start message
    while (!engine->finished()) { //keeps on taking user input as long as the final state has not been reached
        string line;
        cin>>line;
        engine->handleInput(line); //passes input to the handleInput(string) method to pass through the phases depending on the user's input
    }
   
}

