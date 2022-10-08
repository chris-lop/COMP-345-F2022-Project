#pragma once

#include<string>
#include <iostream>
#include "Player.h"

void testGameStates();

class GameEngine
{
   
    private:
    int number;
public:
int getNumber();
void setNumber(int num);
//constructor and destructor
GameEngine();
~GameEngine();
GameEngine(int number);
  //copy constructor
    GameEngine(const GameEngine& g1);

    GameEngine& operator=(const GameEngine& ga);
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
