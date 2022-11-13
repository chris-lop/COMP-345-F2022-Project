#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Map.h"
#include "CommandProcessor.h"
#include "LoggingObserver.h"
#include <string>
class Order;
class ILoggable;
class Subject;

class GameEngine : public ILoggable, public Subject
{
private:
    string state;
    Map *gameMap;

    // active game players
    vector<Player *> gamePlayers;
    // players without territories removed from the game
    vector<Player *> removedPlayers;

public:
    // constructor
    GameEngine();
    GameEngine(Map *gameMap, vector<Player *> gamePlayers);
    // destructor
    ~GameEngine();

    // stream operators
    friend std::ostream &operator<<(std::ostream &strm, const GameEngine &g);
    friend std::istream &operator>>(std::istream &in, GameEngine &g);

    // setters
    void setState(string state);
    void setMap(Map *gameMap);
    void setPlayers(vector<Player *> gamePlayers);

    // getters
    string getState();
    Map *getMap();
    vector<Player *> getPlayers();
    vector<Player *> getRemovedPlayers();

    // stream operators
    friend std::ostream &operator<<(std::ostream &strm, const GameEngine &g);
    friend std::istream &operator>>(std::istream &in, GameEngine &g);

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
    string issueOrders();

    // prints out orders are executed
    void executeOrders();

    // prints out win
    void win();

    // prints out message at start of the game
    void startMessage();

    // boolean checks whether last state has been reached or not
    bool finished();

    // A2 functions
    // function for GameLogObserver
    void transition();

    // main game play loop
    bool mainGameLoop(std::vector<Player *> players, Map *graph);

    // reinforcement phase
    void reinforcementPhase(Player *player, Map *graph);

    // issue orders phase
    void issueOrdersPhase(vector<Player *> player);

    // execute orders phase
    bool executeOrdersPhase();

    vector<char *> directory();

    // startup phase
    void startupPhase(CommandProcessor *cp);

    // ILoggable method
    std::string stringToLog();

}; // end of class GameEngine

// free function
void testGameStates();

// A2 free function
void testMainGameLoop();

void testStatUpPhase();
