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
    GameEngine();
   ~GameEngine();
  
    
   friend std::ostream& operator << (std::ostream& strm, const GameEngine& g);
    friend std::istream& operator >> (std::istream& in, GameEngine& g);
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
};
