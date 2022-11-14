#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"
#include "CommandProcessor.h"

// The main driver function that will run all the test driver functions
int main(int argc, char *argv[])
{

    string commandLineArg = "";
    for (int i = 1; i < argc; i++)
    {
        std::cout << argv[i] << endl;
        if (argv[i][0] == '-') {
            // If there's a dash, do not add it to commandLineArg
            commandLineArg = commandLineArg + (argv[i] + 1) + "\t";
        } else {
            commandLineArg = commandLineArg + argv[i] + "\t";
        }
    }
    if (commandLineArg.find("console") == string::npos && commandLineArg.find("file") == string::npos)
    {
        std::cout << "Invalid command argument" << endl;
        exit(1);
    }
    
    // Part 1
    // testCommandProcessor(commandLineArg);
    // Part 2
    // testStatUpPhase(commandLineArg);
    // Part 3
    // testMainGameLoop();
    // Part 4
    // testOrderExecution();
    // Part 5
    testLoggingObserver(commandLineArg);
}
