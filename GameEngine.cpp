#include <iostream>
#include<string>
#include "GameEngine.h"
#include"Player.h"
using namespace std;
 Order::Order()
 {
     
 }
 
 Order::Order(std::string order)
 {
     this->order=order;
 }
 
 //input
 std::istream& operator >> (std::istream& in, Order& ord){
    std::cout << "Enter your order: ";
    in >> ord.order;
    return in;
}
//output
std::ostream& operator << (std::ostream& strm, const Order& ord){
    strm << "This order is: " << ord.order << std::endl;
    return strm;
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
   cout<<"enter the name of the player";
   cin>>namee;
   Player* pl=new Player(namee);
   cout << *pl;
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




