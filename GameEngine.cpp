

#include <iostream>
#include<string>
#include "GameEngine.h"
#include"Player.h"
#include "Orders.h"
using namespace std;



void GameEngine::startMessage() {
    cout << "Now in start state. Valid input: loadmap" << endl;
}

GameEngine::GameEngine(): state(0){
}
GameEngine::~GameEngine()
{
    
}
 std::istream& operator >> (std::istream& in, GameEngine& g){
    std::cout << "Enter state: ";
    in >> g.state;
    return in;
}

std::ostream& operator<<(std::ostream &strm, const GameEngine &g){
   return strm<<"current state is "<<g.state<<endl;
}

void GameEngine::setState(int st)
{
    state=st;
}
int GameEngine::getState()
{
    return state;
}


void GameEngine::loadMap() {
    cout << "Loading map..." << endl;
}

void GameEngine::validateMap() {
    cout << "Validating map..." << endl;
}
void GameEngine::addPlayers()
{
    string name;
    cout<<"enter the name of the palyer."<<endl;
    cin>>name;
    Player* p=new Player(name);
    cout<<*p;
}
void GameEngine::assignReinforcement()
{
    cout<<"assigning reinforcements..."<<endl;
}
void GameEngine::issueOrders()
{
    string type;
    do{
    
    cout<<"enter your order."<<endl;
    cin>>type;
    if(type!="bomb"&&type!="blockade"&&type!="airlift"&&type!="negotiate"&&type!="deploy"&&type!="advance")
    cout<<"invalid type. valid types: bomb, bloackade, airlift, negotiate, deploy, advance."<<endl;
     Order* order = nullptr;
            if (type == "bomb") {
                order = new Bomb();
            } else if (type == "blockade") {
                order = new Blockade();
            } else if (type == "airlift") {
                order = new Airlift();
            } else if (type == "negotiate") {
                order = new Negotiate();
            } else if (type == "deploy") {
                order = new Deploy();
            } else if (type == "advance") {
                order = new Advance();
            } 
            if (order != nullptr) {
                cout<<*order << endl;
            }
    }
    while(type!="bomb"&&type!="blockade"&&type!="airlift"&&type!="negotiate"&&type!="deploy"&&type!="advance");
}
void GameEngine::executeOrders()
{
    cout<<"executing orders..."<<endl;
}

void GameEngine::win()
{
    cout<<"you win."<<endl;
}

void GameEngine::handleInput(std::string line) {
    if (state == 0) {
        // State: start
        // valid inputs: loadmap
        if (line == "loadmap") {
            loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = 1;
        } else {
            cout << "Invalid command. Valid commands: loadmap" << endl;
        }
    } else if (state == 1) {
        // State: map loaded
        // Valid inputs: loadmap, validatemap
        if (line == "loadmap") {
            loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = 1;
        } else if (line == "validatemap") {
            validateMap();
            cout << "Map now validated, you are in validated state. Valid input: addplayer" << endl;
            state = 2;
        }
        else{
            cout<<"Invalid command. Valid commands: loadmap, validatemap."<<endl;
        }
    } else if (state == 2) {
        // State: map validated
        // Valid input: addplayer
        if (line == "addplayer") {
            addPlayers();
             cout<<"you are now in players added state. Valid input: addplayer, assigncountries."<<endl;
            
            state = 3;
        
        }
         else {
            cout << "Invalid command. Valid command: addplayer" << endl;
        }
    }
    else if(state==3){
        //state: players added
        //valid input: addplayer, assigncountries
        if(line=="addplayer")
        {
            addPlayers();
             cout<<"you are now in players added state. Valid input: addplayer, assigncountries."<<endl;
             
            state = 3;
        }
        else
        if(line=="assigncountries")
        {
             assignReinforcement();
             cout<<"you are now in assign reinforcement state. Valid input: issueorder."<<endl;
            
            state=4;
            
        }
        else
        cout<<"Invalid command. Valid commands: addplayer, assigncountries."<<endl;
    }
    else
    if(state==4){
        //state assign reinforcement
        //valid input: issueorder
        if(line=="issueorder"){
            issueOrders();
            cout<<"you are now in the issue orders state. Valid input: issueorder, endissueorders."<<endl;
            
            state=5;
        }
        else
        cout<<"Invalid command. Valid command: issueorder. "<<endl;
    }
    else
    if(state==5){
        if(line=="issueorder")
        {
             issueOrders();
             cout<<"you are now in the issue orders state. Valid input: issueorder, endissueorders."<<endl;
           
            state=5;
        }
        else
        if(line=="endissueorders")
        {
            executeOrders();
            cout<<"You are now in the execute orders state. Valid input: execorder, endexecorders, win."<<endl;
        state=6;
            
        }
        
        else
        {
            cout<<"Invalid input. valid commands: issueorder, endissueorders."<<endl;
        }
    }
    else
    if(state==6){
        if(line=="execorder"){
            executeOrders();
            cout<<"you are now in the execute orders state. valid input: execorder, endexecorders, win."<<endl;
            state=6;
            
        }
        else
        if(line=="endexecorders"){
             assignReinforcement();
            cout<<"you are now in assign reinforcement state. Valid input: issueorder."<<endl;
           
            state=4;
        }
        else
        if(line=="win")
        {
            win();
            cout<<"you are now in the win state. valid input: end, play."<<endl;
            state=7;
        }
        
    }
    else
    if(state==7){
        if(line=="play")
        {
            
            startMessage();
            state=0;
        }
        else
        if(line=="end")
        {
            cout<<"Game finishing..."<<endl;
            state=8;
        }
        else
        cout<<"Invalid command. valid commands: play, end."<<endl;
        
    }
}

bool GameEngine::finished() {
    return state == 8;
}



