#pragma once

#include<string>
#include <iostream>
#include "Player.h"

void testGameStates();

class GameEngine
{
   
    
public:
   //constructor
   GameEngine();
   //destructor
   ~GameEngine();
   
   //stream insertion operator
    friend std::ostream& operator << (std::ostream& strm, const GameEngine& g);
    friend std::istream& operator >> (std::istream& in, GameEngine& g);

  void start();
   void loaded();
   void validated();
   void assign();
   void issue();
   void execute();
   void win();
};


