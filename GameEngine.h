#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Map.h"
#include <string>
class Order;

class GameEngine
{
private:
    int state;

public:
    // constructor
    GameEngine();
    // destructor
    ~GameEngine();

    // stream operators
    friend std::ostream &operator<<(std::ostream &strm, const GameEngine &g);
    friend std::istream &operator>>(std::istream &in, GameEngine &g);

    // setters and getters
    void setState(int state);
    int getState();

    // takes commands as input and passes through states accordingly
    void handleInput(std::string line);

    // prints out map is loaded
    void loadMap();

    // prints out map is validated
    void validateMap();

    // takes player's name as an input and creates a player
    void addPlayers();

    // prints out reinforcement is aasigned
    void assignReinforcement();

    // takes order as input and creates an order
    Order *issueOrders();

    // prints out orders are executed
    void executeOrders();

    // prints out win
    void win();

    // prints out message at start of the game
    void startMessage();

    // boolean checks whether last state has been reached or not
    bool finished();

    // A2 functions
    bool mainGameLoop(std::vector<Player *> players, Map *graph);
    void reinforcementPhase(Player *player, Map *graph);
    void issueOrdersPhase(Player *player);
    void executeOrdersPhase();
    void startupPhase();
    // void printMapNames();

}; // end of class GameEngine

// free function
void testGameStates();

// A2 free function
void testMainGameLoop();

void testGameEngine();
