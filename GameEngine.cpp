#include <iostream>
#include<string>
#include<cmath>
#include<vector>
#include <algorithm>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
using namespace std;


//GameEngine class
//start message
void GameEngine::startMessage() {
    cout << "Now in start state. Valid input: loadmap" << endl;
}

//Default Constructor
GameEngine::GameEngine(): state(0){
    this->state=0;
    this->gameMap = new Map();
    this->gamePlayers = {};
    this->removedPlayers = {};
}

GameEngine::GameEngine(Map* gameMap, vector <Player*> gamePlayers){
    this->state = 0;
    this->gameMap = gameMap;
    this->gamePlayers = gamePlayers;
    this->removedPlayers = {};
}

//GameEngine destructor
GameEngine::~GameEngine()
{
    delete gameMap;
    for(Player* p: gamePlayers){
        delete p;
    }

    for(Player* p: removedPlayers){
        delete p;
    }
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

//setters
void GameEngine::setState(int st)
{
    this->state=st;
}

void GameEngine::setMap(Map* gameMap){
    this->gameMap = gameMap;
}

void GameEngine::setPlayers(vector <Player*> gamePlayers){
    this->gamePlayers = gamePlayers;
}

//getters
int GameEngine::getState()
{
    return state;
}

Map* GameEngine::getMap(){
    return this->gameMap;
}

vector <Player*> GameEngine::getPlayers(){
    return this->gamePlayers;
}

vector <Player*> GameEngine::getRemovedPlayers(){
    return this->removedPlayers;
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
string GameEngine::issueOrders()
{
    string type;
    do{
        cout<<"Enter your order: "<<endl;
        cin>>type;
        if(type!="bomb"&&type!="blockade"&&type!="airlift"&&type!="negotiate"&&type=="deploy"&&type!="advance") {
            cout<<"invalid type. valid types: bomb, bloackade, airlift, negotiate, deploy, advance."<<endl;
        }
    }
    while(type!="bomb"&&type!="blockade"&&type!="airlift"&&type!="negotiate"&&type=="deploy"&&type!="advance");

    return type;
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
void GameEngine::reinforcementPhase(Player* p, Map* graph){
    //For each player, # army units = (# territories owned)/3, and min. 3 units
    if(std::floor(p->get_trt().size()/3) <= 3){
        p->set_armyUnit(p->get_armyUnit()+3);
    }
    else{
        int additional_unit = std::floor(p->get_trt().size()/3);
        p->set_armyUnit(p->get_armyUnit()+additional_unit);
    }


    //Country control bonus value
    //continentsList: map STL with <continent_name, bonus_value>
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

    std::cout<<"Player "<< p->get_name() << "'s total army units: "<<p->get_armyUnit()<<std::endl;

}

//issueOrdersPhase(): each player issue orders
void GameEngine::issueOrdersPhase(vector<Player*> players){
    // Execute issueOrder in a round-robin fashion
    for(Player* p: players)
    {
        p->issueOrder();
    }
    cout << "All players have issued their orders. Now executing all player orders..." << endl;
}

//To TEST
//executeOrdersPhase(): execute the top order on the list of orders of each player 
bool GameEngine::executeOrdersPhase(){
    bool winner = false;
    bool gameplay = true;

    while(gameplay){
        //for each player, execute one order
        for (int i = 0; i<this->getPlayers().size(); i++){
            std::cout<<"Current turn: "<<this->getPlayers().at(i)->get_name()<<std::endl;

            //if the order list is empty
            if(this->getPlayers().at(i)->get_olst()->getOrder().size() == 0){
                std::cout<<"Player has no more order to execute.\nSkiping turn.\n\n";
            }
            //if the order list is not empty, execute the first order
            else{
                std::cout<<"Executing next order in the order list...\n";
                this->getPlayers().at(i)->get_olst()->getOrder().at(0)->execute();
                //once the order is executed, remove from the list
                std::cout<<"Order executed and removed from the player's order list.\n\n";
                this->getPlayers().at(i)->get_olst()->remove(this->getPlayers().at(i)->get_olst()->getOrder().at(0));
            }

            //if any player of the game does not own any territories after executing current order, remove from the game
            for (int i=0; i<this->getPlayers().size();i++){
                //the removed player will be stored in a vector in case the players re-play the game at the end
                if(this->getPlayers().at(i)->get_trt().size()==0){
                    std::cout<<"Player "<<this->getPlayers().at(i)->get_name()<<" does not own any territories.\n";
                    this->getRemovedPlayers().push_back(this->getPlayers().at(i));
                    //remove player from the active game player list
                    vector <Player*>::iterator it;
                    it = remove(this->getPlayers().begin(),this->getPlayers().end(), this->getPlayers().at(i));
                    std::cout<<"Player "<<this->getPlayers().at(i)->get_name()<<" is removed from current game.\n";
                }
            }

            //if a player owns all territories of the map after executing order, stop the gameplay
            if (this->getPlayers().at(i)->get_trt().size()==this->getMap()->territories.size()){
                winner = true;
                gameplay = false;
                std::cout<<"Player now owns all the territories of the game map.\n\n";
                break;
            }
            //if the player does not own all the territories of the map after executing order, continue to the next player
            else{
                winner = false;
                gameplay = true;
            }

            //verify if all players finished executing orders and finish this game play
            int count = 0;
            for (int i = 0; i<this->getPlayers().size(); i++){
                if(this->getPlayers().at(i)->get_olst()->getOrder().size() == 0){
                    count++;
                }
            }
            if(count==this->getPlayers().size()){
                gameplay = false;
            }
        }//end of for
    }//end of while


    //let the main game loop know if there is a winner
    return winner;

}

//mainGameLoop(): calling 3 phases
bool GameEngine::mainGameLoop(std::vector <Player*> players, Map* graph){
    bool finished = false;
    int num_trt = graph->territories.size();
    bool winner = false;
    string winPlayer;

    //verify if any player owns all territories
    for (Player* p: players){
        //player owns all territories of the map
        if(p->get_trt().size() == num_trt){
            winner = true;
            winPlayer = p->get_name();
            break;
        }
        //player does not own all territories of the map
        else{
            continue;
        }
    }

    if(winner){
        std::cout<<"Player "<<winPlayer<<" conquered all territories of the map and won the game."<<std::endl;
        finished = true;
    }

    else{
        
        //Phase 1: Reinforcement --> call reinforcementPhase() in round-robin
        std::cout<<"#";
        assignReinforcement();
        for (Player* p : players){
            std::cout<<"\nCurrent turn: "<<p->get_name()<<std::endl;
            reinforcementPhase(p, graph);
        }
        std::cout<<"\n<<<reinforcement phase complete...>>>\n";

        //Phase 2: issue Orders --> call issueOrdersPhase() in round-robin
        std::cout<<"\n#issueing orders...\n";
        issueOrdersPhase(gamePlayers);
        std::cout<<"\n<<<issue order phase complete>>>\n";

        //Phase 3: execute Orders --> call executeOrdersPhase() in round-robin
        finished = executeOrdersPhase();

        //to test if everything's working
        //TO REMOVE when Phase 3 is complete to test the loop
        finished=true;
    }

    return finished;   
}