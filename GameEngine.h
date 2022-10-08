#pragma once

#include<string>
#include <iostream>
#include "Player.h"

void testGameStates();

class GameEngine
{
   
    
public:
  void start();
   void loaded();
   void validated();
   void assign();
   void issue();
   void execute();
   void win();
};


