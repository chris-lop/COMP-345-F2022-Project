#include <iostream>
#include<string>
#include "GameEngine.h"
#include"Player.h"
using namespace std;

void GameEngine::start()
{
cout<<"loading map..."<<endl;
   //m.loadMap(); //assuming this is the method used to load a map
 cout<<"map loaded."<<endl;
}

void GameEngine::loaded()
{
    cout<<"validating map..."<<endl;
    // validateMap(); 
    cout<<"map validated."<<endl;
}

void GameEngine::validated()
{
   string namee;
   cout<<"enter the name of the player";
   cin>>namee;
   Player* pl=new Player(namee);
   cout <<"This player is: "<< pl->get_name() << endl;
}
void GameEngine::assign()
{
    cout<<"assigning reinforcement";
}
void GameEngine::issue()
{
    
}
void GameEngine::execute()
{
    
}




