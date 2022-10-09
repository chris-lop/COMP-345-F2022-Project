
#include <iostream>

#include "GameEngine.h"
#include <string>
using std::cin; using std::cout; using std::string; using std::endl;

void testGameStates() {
    GameEngine *engine = new GameEngine();
    engine->startMessage();
    while (!engine->finished()) {
        string line;
        cin>>line;
        engine->handleInput(line);
    }
   
}

