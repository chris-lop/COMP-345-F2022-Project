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
        commandLineArg = commandLineArg + argv[i] + "\t";
    }
    if (commandLineArg.find("console") != 0 || commandLineArg.find("file") != 0)
    {
        exit(1);
    }
    // add validationg

    // Part 1: Map
    // testLoadMaps();

    // removed testPlayer() from A1 and commented out all test functions from A1- HL

    // Part 3: Orders List
    // testOrderExecution();
    // Part 4: Cards
    // testCards();
    // Part 5: Game Engine
    //  testGameStates();

    // A2 Part 3
    //  testMainGameLoop();

    // Part 3: Orders List
    //  testOrderExecution();
    // Part 4: Cards
    // testCards();
    // Part 5: Game Engine
    //  testGameStates();

    // A2 Part 3
    // testCommandProcessor(commandLineArg);
    // TESTED working
    // testStatUpPhase(commandLineArg);
    testLoggingObserver(commandLineArg);
    // testMainGameLoop();
}
