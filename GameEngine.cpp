

#include <iostream>
#include<string>
#include "GameEngine.h"
#include"Player.h"
using namespace std;
GameEngine::GameEngine()
{
    number=0;
}
GameEngine::GameEngine(int number)
{
    this->number=number;
}
GameEngine::~GameEngine()
{
    
}
 std::istream& operator >> (std::istream& in, GameEngine& g){
    std::cout << "Enter number of players: ";
    in >> g.number;
    return in;
}

std::ostream& operator<<(std::ostream &strm, const GameEngine &g){
   return strm<<"number of players is "<<g.number<<endl;
}

void GameEngine::setNumber(int num)
{
    number=num;
}
int GameEngine::getNumber()
{
    return number;
}
//copy constructor
GameEngine::GameEngine(const GameEngine& g1){
    this->number=g1.number;
}

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
   cout<<"enter the name of the player"<<endl;
   cin>>namee;
   Player* pl=new Player(namee);
   cout << *pl;
}
void GameEngine::assign()
{
    cout<<"assigning reinforcement"<<endl;
}
void GameEngine::issue()
{
    
}
void GameEngine::execute()
{
    
}
