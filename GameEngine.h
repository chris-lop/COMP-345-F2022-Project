#pragma once

#include<string>
#include <iostream>
#include <vector>
#include "Player.h"
#pragma once
#include <string>

class GameEngine {
private:
    int state;
public:
    //constructor
    GameEngine();
    //destructor
   ~GameEngine();
  
    //stream operators
   friend std::ostream& operator << (std::ostream& strm, const GameEngine& g);
    friend std::istream& operator >> (std::istream& in, GameEngine& g);
    
    //setters and getters
    void setState(int state);
    int getState();
    
    //takes commands as input and passes through states accordingly
    void handleInput(std::string line);
    
    //prints out map is loaded
    void loadMap();
    
    //prints out map is validated
    void validateMap();
    
    //takes player's name as an input and creates a player
    void addPlayers();
    
    //prints out reinforcement is aasigned
    void assignReinforcement();
    
    //takes order as input and creates an order
    void issueOrders();
    
    //prints out orders are executed
    void executeOrders();
    
    //prints out win
    void win();
    
    //prints out message at start of the game
    void startMessage();
    
    //boolean checks whether last state has been reached or not
    bool finished();

    //A2 functions
    void mainGameLoop(std::vector <Player*> players, Map* graph);
    void reinforcementPhase(std::vector <Player*> players, Map* graph);
    void issueOrdersPhase(Player* p);
    void executeOrdersPhase();

}; //end of class GameEngine


//free function
void testGameStates();

//A2 free function
void testMainGameLoop();