
#include "GameEngine.h"
#include <iostream>
#include <string>
using namespace std;
void testGameStates()
{  
GameEngine* g=new GameEngine();
cout<<"enter the command to pass through states";
std::string command;
std::string command2;
std::string command3;
std::string command4;
std::string command5;
std::string command6;
std::string command7;

std::string command11;

do{
    
do{
cin>>command;
}
while(command!="loadmap");
g->start();
//map loaded state and we are trying to load or validate map
do
{
    cin>>command2;
    if(command2=="loadmap")
    g->start();
    if(command2=="validatemap")
    g->loaded();
}
while(command2=="loadmap"||(command2!="loadmap"&&command2!="validatemap"));
    //we want to add players now
   
    do
{
      cin>>command3;  
      if(command3=="addplayer")
      g->validated();
}
while(command3=="addplayer"||(command3!="assigncountries"&&command3!="addplayer"));

//here we are trying to issue order
do{//this loop assigns reinforcement
    if(command3=="assigncountries"||command6=="endexecorders")
g->assign();
    do{ //this loop issues order
        cin>>command4;
        if(command4=="issueorder")
        {
            string ordert;
            cout<<"enter your order";
            cin>>ordert;
            Order* ord=new Order(ordert);
            cout<<*ord;
        }
    }
    while(command4=="issueorder" || (command4!="issueorder"&&command4!="endissueorders"));
    if(command4=="endissueorders")
    {
        do{ //this loop executes orders
        cout<<"executing orders..."<<endl;
            cin>>command5;
            if(command5=="execorder")
            {
                cout<<"orders executed"<<endl;
            }
            if(command5=="win")
            {
                do{
                cin>>command11;
                }
                while(command11!="play"&&command11!="end");
                
            }
            
        }
while(command5=="execorder"||(command5!="execorder"&&command5!="endexecorders"&&command5!="win"));
    }
    //here we know we got win
 
}
while(command5=="endexecorders");


}while(command11=="play");
  

}