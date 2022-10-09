#pragma once

#include<string>
#include <iostream>
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
    
    
    void handleInput(std::string line);
    void loadMap();
    void validateMap();
    void addPlayers();
    void assignReinforcement();
    void issueOrders();
    void executeOrders();
    void win();
    void startMessage();
    bool finished();
}; //end of class GameEngine


//free function
void testGameStates();
