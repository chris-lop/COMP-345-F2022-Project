
#include <iostream>
#include<string>
#include "GameEngine.h"
#include"Player.h"
#include "Orders.h"
using namespace std;


//GameEngine class
//start message
void GameEngine::startMessage() {
    cout << "Now in start state. Valid input: loadmap" << endl;
}

//constructor and destructor
GameEngine::GameEngine(): state(0){
}

//GameEngine destructor
GameEngine::~GameEngine()
{
    
}

//stream operators
 std::istream& operator >> (std::istream& in, GameEngine& g){
    std::cout << "Enter state: ";
    in >> g.state;
    return in;
}

std::ostream& operator<<(std::ostream &strm, const GameEngine &g){
   return strm<<"current state is "<<g.state<<endl;
}

//setters and getters
void GameEngine::setState(int st)
{
    state=st;
}
//getter for state
int GameEngine::getState()
{
    return state;
}

//loads the map
void GameEngine::loadMap() {
    cout << "Loading map..." << endl;
}

//validates the map, prints out that the map got validated
void GameEngine::validateMap() {
    cout << "Validating map..." << endl;
}

//takes player's name as input from the user and creates a player
void GameEngine::addPlayers()
{
    string name;
    cout<<"enter the name of the palyer."<<endl;
    cin>>name;
    Player* p=new Player(name);
    cout<<*p;
    delete p;
}

//prints out assigning reinforcement
void GameEngine::assignReinforcement()
{
    cout<<"assigning reinforcements..."<<endl;
}

//takes user's input and creates an order depending on input
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
        delete order;
    }
    while(type!="bomb"&&type!="blockade"&&type!="airlift"&&type!="negotiate"&&type!="deploy"&&type!="advance");
}

//executes orders, prints out executing orders
void GameEngine::executeOrders()
{
    cout<<"executing orders..."<<endl;
}

//prints out you win
void GameEngine::win()
{
    cout<<"you win."<<endl;
}

//moves through the states depending on the user's command which will be passed to the function as a parameter
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
    //players added state
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
    //the issue orders state
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
    //the issue orders state
    if(state==5){
        if(line=="issueorder")
        {
             issueOrders();
             cout<<"you are now in the issue orders state. Valid input: issueorder, endissueorders."<<endl;
           
            state=5;
        }
        else
        //the execute orders state
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
    //the execute orders state
    if(state==6){
        if(line=="execorder"){
            executeOrders();
            cout<<"you are now in the execute orders state. valid input: execorder, endexecorders, win."<<endl;
            state=6;
            
        }
        else
        //assign reinforcement state
        if(line=="endexecorders"){
             assignReinforcement();
            cout<<"you are now in assign reinforcement state. Valid input: issueorder."<<endl;
           
            state=4;
        }
        else
        //the win state
        if(line=="win")
        {
            win();
            cout<<"you are now in the win state. valid input: end, play."<<endl;
            state=7;
        }
        else{
            cout<<"invalid command. valid input: execorder, endexecorders, win."<<endl;
        }
        
    }
    else
    //pplay again or end the game
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

//checks whether the final state has been reached or not
bool GameEngine::finished() {
    return state == 8;
}



