
#include <iostream>
#include<string>
#include<cmath>
#include<vector>
#include <algorithm>
#include "GameEngine.h"
#include"Player.h"
#include"Map.h"
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

//A2 functions
//reinforcementPhase(): provide each players with the appropriate army units number
void GameEngine::reinforcementPhase(std::vector <Player*> players, Map* graph){
    //For each player, # army units = (# territories owned)/3, and min. 3 units
    for (Player* p: players){
        if(std::floor(p->get_trt().size()/3) <= 3){
            p->set_armyUnit(p->get_armyUnit()+3);
        }
        else{
            int additional_unit = std::floor(p->get_trt().size()/3);
            p->set_armyUnit(p->get_armyUnit()+additional_unit);
        }
    }

    //Country control bonus value
    //continentsList = map STL with <continent_name, bonus_value>
    map<string, int> continent_bonus = graph->continentsList;

    //vector string to store the continent names
    string continents[continent_bonus.size()];
    map<string, int>::iterator itr;
    int count = 0;
    for (itr = continent_bonus.begin(); itr != continent_bonus.end(); ++itr) {
        continents[count]=(itr->first);
        count+=1;
    }

    //array to store each continent's respective territories
    vector<Territory*> t_continents[continent_bonus.size()];
    
    //read the game map to store continent information
    for(int i=0; i<continent_bonus.size(); i++){
        for (Territory* t: graph->territories){
            string new_c =*(t->getContinent());
            if(new_c==continents[i]){
                t_continents[i].push_back(t);
            }
        }
    }

    //verify if each player owns all territories of a continent
    for(Player* p: players){
        for(int i=0; i<continent_bonus.size(); i++){
            int increment = 0;
            for(Territory* vt: t_continents[i]){
                vector<Territory*> own_trt = p->get_trt();
                if (find(own_trt.begin(), own_trt.end(), vt) != own_trt.end()) {
                    increment = increment+1;
                }
                //don't increment if a territory of the given continent is not found
                else{
                    continue;
                }
            }
            //if player owns all territories of a given continent
            if(increment==t_continents[i].size()){
                //find the bonus value corresponding to the continent
                auto it = continent_bonus.find(continents[i]);
                int bonus = it->second;
                p->set_armyUnit(p->get_armyUnit()+bonus);
            }
            //else, continue the verification with the next continent
            else{
                continue;
            }
        }
    }    

    for(Player* p: players){
        std::cout<<"Player "<< p->get_name() << "'s total army units: "<<p->get_armyUnit()<<std::endl;
    }
}

//issueOrdersPhase(): each player issue orders
void GameEngine::issueOrdersPhase(std::vector <Player*> players){
    
    for (Player* p: players){
    vector <Territory*> trt_attack = p->toAttack();
    vector <Territory*> trt_defend = p->toDefend();
    
    //Notify player of the current list of territories to defend and to attack
    std::cout<<"Issue orders for "<<p->get_name()<<std::endl;
    std::cout<<"Player's territories to defend: "<<std::endl;
    for (Territory* t: trt_defend){
        std::cout<< *(t->getTerritoryName()) <<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Player's territories to attack: "<<std::endl;
    for (Territory* t: trt_attack){
        std::cout<< *(t->getTerritoryName()) <<" ";
    }
    std::cout<<std::endl;

    //Issue deploy order
    //If no more army units, proceed to issue other orders
    //If player has more army units, proceed to issue deploy() or break out from order issue phase
    bool issue = true;
    while(issue){
        p->issueOrder();
        bool yn = true;
        while(yn){
            std:: string answer;
            std::cout<< "Add more order? (Y/N)"<<std::endl;
            std::cin>>answer;
            if(answer=="Y"){
                issue=true;
                yn = true;
                p->issueOrder();
            }
            else if(answer=="N")
            {
               issue=false;
               yn = false;
            }
            else{
                std::cout<<"Please enter the correct answer."<<std::endl;
                yn = true;
            }
        }
    }

    //Orders following deploy()
    }
}

//executeOrdersPhase(): execute the top order on the list of orders of each player 

//mainGameLoop(): calling 3 phases
void GameEngine::mainGameLoop(std::vector <Player*> players, Map* graph){

    //Phase 1: Reinforcement
    reinforcementPhase(players, graph);

    //Phase 2: issue Orders --> call issueOrdersPhase() in round-robin
    issueOrdersPhase(players);
    
    //Phase 3: execute Orders --> call executeOrdersPhase() in round-robin
}


