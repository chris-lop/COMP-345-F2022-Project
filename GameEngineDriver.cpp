#include "GameEngine.h"
#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;
void testGameStates()
{ 
std::cout << "\n### Test Game States ### \n" << std::endl; 
GameEngine* g=new GameEngine();

/*message to prompt user to enter the correct input*/
string command_error= "***Wrong command entered. Try again.\nMake sure to enter the exact command to pass through states.***";
cout<< "***Make sure to enter the exact command to pass through states.***"<<endl;
std::string command;
std::string command2;
std::string command3;
std::string command4;
std::string command5;
std::string command6;
std::string command7;
std::string command11;
int n=0;
int m=0;
int x=0;
do{
    cout<<"Starting Game Engine.\nYou are currently in start phase."<<endl;
    cout<<"Enter loadmap to start the game."<<endl;
do{
cin>>command;
if(command!="loadmap")
cout<<"Wrong command entered. Try again.\n"<< command_error <<endl;
}
while(command!="loadmap");
g->start();
//map loaded state and we are trying to load or validate map

cout<<"***\nYou are currently in map loaded phase."<<endl;

do
{
    cout<<"Enter loadmap to re-load a new map or validatemap to validate the current map."<<endl;
    cin>>command2;
    if(command2!="loadmap"&&command2!="validatemap")
    cout<< command_error <<endl;
    if(command2=="loadmap")
    g->start();
    if(command2=="validatemap")
    g->loaded();
}
while(command2=="loadmap"||(command2!="loadmap"&&command2!="validatemap"));
    //we want to add players now
   
    do
{

    cout<<"please enter command addplayer to add a player, then enter assigncountries when you are done adding players."<<endl;
      cin>>command3; 
      if(command3=="assigncountries"&&n==0)
      cout<<"you did not add a player, please add a player before you can move on to the next phase"<<endl;
      if(command3!="addplayer"&&command3!="assigncountries")
      cout<<"wrong command please try again"<<endl;
      if(command3=="addplayer")
      {
      g->validated();
      n=n+1;
      }
      
}
while(command3=="addplayer"||(command3!="assigncountries"&&command3!="addplayer")||(command3=="assigncountries"&&n==0));

//here we are trying to issue order
do{//this loop assigns reinforcement
    if(command3=="assigncountries"||command6=="endexecorders")
g->assign();
    do{ //this loop issues order
    cout<<"enter the command issueorder to issue an order, then when you are done enter the command endissueorders to move to the next phase."<<endl;
        cin>>command4;
        if(command4=="endissueorders"&&m==0)
        cout<<"you did not issue an order, please issue an order before moving on to the next phase"<<endl;
        if(command4!="issueorder"&&command4!="endissueorders")
        cout<<"wrong command please try again."<<endl;
        if(command4=="issueorder")
        {
            m=m+1;
            string type;
            cout<<"enter your order"<<endl;
            cin>>type;

            Order* order = nullptr;
            if (type == "bomb") {
                order = new Bomb();
            } else if (type == "reinforcement") {
                cout << "Reinforcement card played, no order" << endl;
            } else if (type == "blockade") {
                order = new Blockade();
            } else if (type == "airlift") {
                order = new Airlift();
            } else if (type == "diplomacy") {
                order = new Negotiate();
            }
            if (order != nullptr) {
                cout<<*order;
            }
        }
    }
    while(command4=="issueorder" || (command4!="issueorder"&&command4!="endissueorders")||(command4=="endissueorders"&&m==0));
    if(command4=="endissueorders"&&m!=0)
    {
        do{ //this loop executes orders
        cout<<"enter the command execorder to execute your orders, then enter the command win to move to the next phase or the command endexecorders to go back to assign reinforcement phase"<<endl;
            cin>>command5;
            if(command5!="execorder"&&command5!="endexecorders"&&command5!="win")
            cout<<"wrong command please try again."<<endl;
            if(command5=="endexecorders"&&x==0)
            cout<<"you did not execute orders, please execute your order before moving to the next phase."<<endl;
            if(command5=="win"&&x==0)
            cout<<"you can not win before executing orders, please execute your order before moving to the next phase"<<endl;
            
            if(command5=="execorder")
            {
                cout<<"orders executed"<<endl;
                x=x+1;
            }
            if(command5=="win"&&x!=0)
            {
                do
                {
                cout<<"enter the command play to restart or end to end the game."<<endl;
                cin>>command11;
                }
                while(command11!="play"&&command11!="end");
                
            }
            
        }
while(command5=="execorder"||(command5=="win"&&x==0)||(command5!="execorder"&&command5!="endexecorders"&&command5!="win")||(x==0&&command5=="endexecorders"));
    }
    //here we know we got win
 
}
while(command5=="endexecorders");


}while(command11=="play");
  
}
