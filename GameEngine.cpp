#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <dirent.h>
#include <random>
#include <iterator>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "CommandProcessor.h"
using namespace std;

// GameEngine class
// start message
void GameEngine::startMessage()
{
    std::cout << "Now in start state. Valid input: loadmap" << endl;
}

// Default Constructor
GameEngine::GameEngine()
{
    this->state = "start";
    this->done=false;
    this->gameMap = new Map();
    this->gamePlayers = {};
    this->removedPlayers = {};
}

GameEngine::GameEngine(Map *gameMap, vector<Player *> gamePlayers)
{
    this->state = "start";
    this->done=false;
    this->gameMap = gameMap;
    this->gamePlayers = gamePlayers;
    this->removedPlayers = {};
}

GameEngine::GameEngine(Map *gameMap, vector<Player *> gamePlayers, vector<Player *> removedPlayers)
{
    this->state = "start";
    this->done=false;
    this->gameMap = gameMap;
    this->gamePlayers = gamePlayers;
    this->removedPlayers = removedPlayers;
}

// GameEngine destructor
GameEngine::~GameEngine()
{
    delete gameMap;
    
    for (Player *p : gamePlayers)
    {
        delete p;
    }

    for (Player *p : removedPlayers)
    {
        delete p;
    }
}

// stream operators
std::istream &operator>>(std::istream &in, GameEngine &g)
{
    std::cout << "Enter state: ";
    in >> g.state;
    return in;
}

std::ostream &operator<<(std::ostream &strm, const GameEngine &g)
{
    return strm << "current state is " << g.state << endl;
}

// setters
void GameEngine::setState(string st)
{
    this->state = st;
    notify(this);
}

void GameEngine::setDeck(Deck *gameDeck)
{
    this->d = gameDeck;
}

void GameEngine::setMap(Map *gameMap)
{
    this->gameMap = gameMap;
}

void GameEngine::setPlayers(vector<Player *> gamePlayers)
{
    this->gamePlayers = gamePlayers;
}

void GameEngine::setRemovedPlayers(vector<Player *> removedPlayers)
{
    this->removedPlayers = removedPlayers;
}
// getters
string GameEngine::getState()
{
    return state;
}

Map *GameEngine::getMap()
{
    return this->gameMap;
}

Deck *GameEngine::getDeck()
{
    return this->d;
}

vector<Player *> GameEngine::getPlayers()
{
    return this->gamePlayers;
}

vector<Player *> GameEngine::getRemovedPlayers()
{
    return this->removedPlayers;
}

// loads the map
void GameEngine::loadMap()
{
    std::cout << "Loading map..." << endl;
}

// validates the map, prints out that the map got validated
void GameEngine::validateMap()
{
    std::cout << "Validating map..." << endl;
}

// takes player's name as input from the user and creates a player
void GameEngine::addPlayers()
{
    string name;
    std::cout << "enter the name of the palyer." << endl;
    cin >> name;
    Player *p = new Player(name);
    std::cout << *p;
    delete p;
}

// prints out assigning reinforcement
void GameEngine::assignReinforcement()
{
    std::cout << "assigning reinforcements..." << endl;
}

// takes user's input and creates an order depending on input
string GameEngine::issueOrders()
{
    string type;
    do
    {
        std::cout << "Enter your order: " << endl;
        cin >> type;
        if (type != "bomb" && type != "blockade" && type != "airlift" && type != "negotiate" && type == "deploy" && type != "advance")
        {
            std::cout << "invalid type. valid types: bomb, bloackade, airlift, negotiate, deploy, advance." << endl;
        }
    } while (type != "bomb" && type != "blockade" && type != "airlift" && type != "negotiate" && type == "deploy" && type != "advance");

    return type;
}

// executes orders, prints out executing orders
void GameEngine::executeOrders()
{
    std::cout << "executing orders..." << endl;
}

// prints out you win
void GameEngine::win()
{
    std::cout << "you win." << endl;
}

bool GameEngine::getDone(){
    return done;
}

// handles the user's commands and passes through the stages of the game
bool GameEngine::playegame(Command *command)
{
    
    if (state == "start")
    {
        // State: start
        // valid inputs: loadmap
        if ((command->getCommand()).find("loadmap") == 0)
        {
            // loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = "maploaded";
            return true;
        }
        else
        {
            cout << "Invalid command. Valid commands: loadmap" << endl;
            return false;
        }
    }
    else if (state == "maploaded")
    {
        // State: map loaded
        // Valid inputs: loadmap, validatemap
        if ((command->getCommand()).find("loadmap") == 0)
        {
            // loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = "maploaded";
            return true;
        }
        else if (command->getCommand() == "validatemap")
        {
            // validateMap();
            cout << "Map now validated, you are in validated state. Valid input: addplayer" << endl;
            state = "mapvalidated";
            return true;
        }
        else
        {
            cout << "Invalid command. Valid commands: loadmap, validatemap." << endl;
            return false;
        }
    }
    else if (state == "mapvalidated")
    {
        // State: map validated
        // Valid input: addplayer
        if ((command->getCommand()).find("addplayer") == 0)
        {
            // addPlayers();
            cout << "you are now in players added state. Valid input: addplayer, gamestart." << endl;

            state = "playersadded";
            return true;
        }
        else
        {
            cout << "Invalid command. Valid command: addplayer." << endl;
            return false;
        }
    }
    // players added state
    else if (state == "playersadded")
    {
        // state: players added
        // valid input: addplayer, assigncountries
        if ((command->getCommand()).find("addplayer") == 0)
        {
            // addPlayers();
            cout << "you are now in players added state. Valid input: addplayer, gamestart." << endl;

            state = "playersadded";
            return true;
        }
        else if (command->getCommand() == "gamestart")
        {

            cout << "starting the game... Valid input: replay, quit." << endl;

            // here game should be played automatically
            cout << "assigning reinforcement." << endl;
            cout << "issuing orders." << endl;
            cout << "executing orders." << endl;
            cout << "enter replay or quit." << endl;
            // then jump to state win
            state = "win";

            // here game should be played automatically
            // then jump to state win
            state = "win";
            return true;
        }
        else
            cout << "Invalid command. Valid commands: addplayer, gamestart." << endl;
        return false;
    }
    else

        if (state == "win")
    {

        if (command->getCommand() == "replay")
        {

            startMessage();
            state = "start";
            return true;
        }
        else if (command->getCommand() == "quit")
        {
            cout << "game ended." << endl;
            done = true;
            return true;
        }
        else
            cout << "invalid command, valid commands are replay, quit." << endl;
        return false;
    }
    return true; // added by marc
}


// A2 functions
// Set the game engine to the correct state when called


// Method providing the string to log
string GameEngine::stringToLog()
{
    return string("The state has transitioned to ") + getState();
}

// reinforcementPhase(): provide each players with the appropriate army units number
void GameEngine::reinforcementPhase(Player *p, Map *graph)
{

    // change state from 'playersadded' to 'assignreinforcement'
    this->setState("assignreinforcement");
    

    std::cout << "Player " << p->get_name() << "'s current army units in the pool: " << p->get_armyUnit() << std::endl;
    std::cout << "Player " << p->get_name() << "'s number of owned territories: " << p->get_trt().size() << std::endl;

    // For each player, # army units = (# territories owned)/3, and min. 3 units
    if (std::floor(p->get_trt().size() / 3) <= 3)
    {
        p->set_armyUnit(p->get_armyUnit() + 3);
    }
    else
    {
        int additional_unit = std::floor(p->get_trt().size() / 3);
        p->set_armyUnit(p->get_armyUnit() + additional_unit);
    }

    // Country control bonus value
    // continentsList: map STL with <continent_name, bonus_value>
    map<string, int> continent_bonus = graph->continentsList;

    // vector string to store the continent names
    string continents[continent_bonus.size()];
    map<string, int>::iterator itr;
    int count = 0;
    for (itr = continent_bonus.begin(); itr != continent_bonus.end(); ++itr)
    {
        continents[count] = (itr->first);
        count += 1;
    }

    // array to store each continent's respective territories
    vector<Territory *> t_continents[continent_bonus.size()];

    // read the game map to store continent information
    for (int i = 0; i < continent_bonus.size(); i++)
    {
        for (Territory *t : graph->territories)
        {
            string new_c = *(t->getContinent());
            if (new_c == continents[i])
            {
                t_continents[i].push_back(t);
            }
        }
    }

    // verify if each player owns all territories of a continent
    for (int i = 0; i < continent_bonus.size(); i++)
    {
        int increment = 0;
        for (Territory *vt : t_continents[i])
        {
            vector<Territory *> own_trt = p->get_trt();
            if (find(own_trt.begin(), own_trt.end(), vt) != own_trt.end())
            {
                increment = increment + 1;
            }
            // don't increment if a territory of the given continent is not found
            else
            {
                continue;
            }
        }

        // if player owns all territories of a given continent
        if (increment == t_continents[i].size())
        {
            // find the bonus value corresponding to the continent
            auto it = continent_bonus.find(continents[i]);
            int bonus = it->second;
            cout << "Player owns all territories of the continent "<<continents[i]<<".\nContinent with bonus value of " << bonus <<" added to the pool." << std::endl;
            p->set_armyUnit(p->get_armyUnit() + bonus);
            
        }
        // else, continue the verification with the next continent
        else
        {
            continue;
        }
    }

    std::cout << "Player " << p->get_name() << "'s new total army units in the pool: " << p->get_armyUnit() << std::endl;
}

// issueOrdersPhase(): each player issue orders
void GameEngine::issueOrdersPhase(vector<Player *> players)
{
    // change state from 'assignreinforcement' to 'issueorders'
    this->setState("issueorders");
   

    // Execute issueOrder in a round-robin fashion
    while (true)
    {
        for (Player *p : players)
        {
            if (p->get_name() == "Neutral Player")
            {
                continue;
            }
            p->issueOrder();
        }

        // Ask if players want to issue more orders
        bool issueMoreOrders = (rand() % 100) < 60;

        if (!issueMoreOrders)
        {
            cout << "Players have decided not to issue more orders" << endl;
            break;
        }
    }
    cout << "All players have issued their orders. Now executing all player orders..." << endl;
}

// To TEST
// executeOrdersPhase(): execute the top order on the list of orders of each player
bool GameEngine::executeOrdersPhase()
{
    // change state from 'issueorders' to 'executeorders'
    this->setState("executeorders");
   
    bool winner = false;
    bool gameplay = true;

    while (gameplay)
    {
        // for each player, execute one order
        for (int i = 0; i < this->getPlayers().size(); i++)
        {
            // skip Neutral Player's turn
            if (this->getPlayers().at(i)->get_name() == "Neutral Player")
            {
                continue;
            }
            std::cout << "Current turn: " << this->getPlayers().at(i)->get_name() << std::endl;

            // if the order list is empty
            if (this->getPlayers().at(i)->get_olst()->getOrder().size() == 0)
            {
                std::cout << "Player has no more order to execute.\nSkiping turn.\n\n";
            }
            // if the order list is not empty, execute the first order
            else
            {
                // order execution
                std::cout << "Executing next order in the order list...\n";
                this->getPlayers().at(i)->get_olst()->getOrder().at(0)->execute();

                string orderType = this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType();
                Order *theOrder = this->getPlayers().at(i)->get_olst()->getOrder().at(0);

                if (orderType == "Bomb")
                {
                    Bomb *cardType = (Bomb *)theOrder;

                    // if order was valid, remove its card from player's hand
                    if (cardType->validate() && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Advance" && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Deploy")
                    {
                        // Check order type, and remove card from player's hand depending on order type
                        string orderType = this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType();

                        for (Card *c : this->getPlayers().at(i)->get_Phand()->cardList())
                        {
                            if (c->getType() == orderType)
                            {
                                this->getPlayers().at(i)->get_Phand()->returnToDeck(c, this->getDeck());
                                break;
                            }
                        }
                    }
                }
                else if (orderType == "Airlift")
                {
                    Airlift *cardType = (Airlift *)theOrder;

                    // if order was valid, remove its card from player's hand
                    if (cardType->validate() && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Advance" && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Deploy")
                    {
                        // Check order type, and remove card from player's hand depending on order type
                        string orderType = this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType();

                        for (Card *c : this->getPlayers().at(i)->get_Phand()->cardList())
                        {
                            if (c->getType() == orderType)
                            {
                                this->getPlayers().at(i)->get_Phand()->returnToDeck(c, this->getDeck());
                                break;
                            }
                        }
                    }
                }
                else if (orderType == "Blockade")
                {
                    Blockade *cardType = (Blockade *)theOrder;

                    // if order was valid, remove its card from player's hand
                    if (cardType->validate() && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Advance" && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Deploy")
                    {
                        // Check order type, and remove card from player's hand depending on order type
                        string orderType = this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType();

                        for (Card *c : this->getPlayers().at(i)->get_Phand()->cardList())
                        {
                            if (c->getType() == orderType)
                            {
                                this->getPlayers().at(i)->get_Phand()->returnToDeck(c, this->getDeck());
                                break;
                            }
                        }
                    }
                }
                else if (orderType == "Negotiate")
                {
                    Negotiate *cardType = (Negotiate *)theOrder;

                    // if order was valid, remove its card from player's hand
                    if (cardType->validate() && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Advance" && this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() != "Deploy")
                    {
                        // Check order type, and remove card from player's hand depending on order type
                        string orderType = this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType();

                        for (Card *c : this->getPlayers().at(i)->get_Phand()->cardList())
                        {
                            if (c->getType() == orderType)
                            {
                                this->getPlayers().at(i)->get_Phand()->returnToDeck(c, this->getDeck());
                                break;
                            }
                        }
                    }
                }

                // If order was an advance order, check if it resulted in a conquered territory
                if (this->getPlayers().at(i)->get_olst()->getOrder().at(0)->getType() == "Advance")
                {
                    Order *anOrder = this->getPlayers().at(i)->get_olst()->getOrder().at(0);
                    Advance *anAdvance = (Advance *)anOrder;

                    // Check if order was an attack
                    if (anAdvance->isAttack())
                    {
                        // check if execution resulted in conquered territory
                        if (anAdvance->getPlayer()->get_name() == anAdvance->getTarget()->getTerritoryOwner()->get_name())
                        {
                            // Award player with a card from deck
                            this->getPlayers().at(i)->get_Phand()->addCard(this->getDeck()->draw());
                        }
                    }
                }

                // once the order is executed, remove from the list
                std::cout << "Order executed and removed from the player's order list.\n\n";
                this->getPlayers().at(i)->get_olst()->remove(this->getPlayers().at(i)->get_olst()->getOrder().at(0));
            }

            // if any player of the game does not own any territories after executing current order, remove from the game
            for (int i = 0; i < this->getPlayers().size(); i++)
            {
                // the removed player will be stored in a vector in case the players re-play the game at the end
                if (this->getPlayers().at(i)->get_trt().size() == 0)
                {
                    vector<Player *> temp1 = this->getPlayers();
                    vector<Player *> tempRemove = this->getRemovedPlayers();
                    std::cout << "Player " << this->getPlayers().at(i)->get_name() << " does not own any territories.\n";
                    tempRemove.push_back(this->getPlayers().at(i));
                    std::cout << "Player " << this->getPlayers().at(i)->get_name() << " is removed from current game.\n";
                    // remove player from the active game player list
                    vector<Player *>::iterator it;
                    it = temp1.begin() + i;
                    temp1.erase(it);
                    this->setPlayers(temp1);
                    this->setRemovedPlayers(tempRemove);

                    std::cout << "Active Players" << std::endl;
                    for (Player *p : this->getPlayers())
                    {
                        std::cout << p->get_name() << std::endl;
                    }
                    std::cout << "Removed Players" << std::endl;
                    for (Player *p : this->getRemovedPlayers())
                    {
                        std::cout << p->get_name() << std::endl;
                    }
                }
            }

            // if a player owns all territories of the map after executing order, stop the gameplay
            if (this->getPlayers().at(0)->get_trt().size() == this->getMap()->territories.size())
            {
                winner = true;
                gameplay = false;
                std::cout << "\nPlayer " << this->getPlayers().at(0)->get_name() << " now owns all the territories of the game map.\n\n";
                break;
            }
            // if the player does not own all the territories of the map after executing order, continue to the next player
            else
            {
                winner = false;
                gameplay = true;
            }

            // verify if all players finished executing orders and finish this game play
            int count = 0;
            for (int i = 0; i < this->getPlayers().size(); i++)
            {
                if (this->getPlayers().at(i)->get_olst()->getOrder().size() == 0)
                {
                    count++;
                }
            }
            if (count == this->getPlayers().size())
            {
                gameplay = false;
            }
        } // end of for
    }     // end of while

    // let the main game loop know if there is a winner
    return winner;
}


// mainGameLoop(): calling 3 phases
bool GameEngine::mainGameLoop(std::vector<Player *> players, Map *graph)
{
    bool finished = false;
    int num_trt = graph->territories.size();
    bool winner = false;
    string winPlayer;

    // verify if any player owns all territories
    for (Player *p : players)
    {
        // player owns all territories of the map
        if (p->get_trt().size() == num_trt)
        {
            winner = true;
            winPlayer = p->get_name();
            if (this->getState() == "executeorders")
            {
                this->setState("win");
            }
            else
            {
                this->setState("win");
                
            }
            break;
        }
        // player does not own all territories of the map
        else
        {
            continue;
        }
    }

    if (winner)
    {
        std::cout << "Player " << winPlayer << " conquered all territories of the map and won the game." << std::endl;
        finished = true;
    }

    else
    {

        // Phase 1: Reinforcement --> call reinforcementPhase() in round-robin
        std::cout << "#";
        assignReinforcement();
        for (Player *p : players)
        {
            if (p->get_name() == "Neutral Player")
            {
                continue;
            }
            std::cout << "\nCurrent turn: " << p->get_name() << std::endl;
            reinforcementPhase(p, graph);
        }
        std::cout << "\n<<<reinforcement phase complete...>>>\n";

        // Phase 2: issue Orders --> call issueOrdersPhase() in round-robin
        std::cout << "\n#issueing orders...\n";
        issueOrdersPhase(gamePlayers);
        std::cout << "\n<<<issue order phase complete>>>\n";

        // Phase 3: execute Orders --> call executeOrdersPhase() in round-robin
        finished = executeOrdersPhase();

        // to test if everything's working
        // TO REMOVE when Phase 3 is complete to test the loop
        finished = true;
    }

    // once removed, replace finished with winner so main game loop is finished when there is a winner
    return winner;
}

vector<string> GameEngine::directory()
{
    DIR *dir;
    struct dirent *diread;
    vector<string> nameOfMaps;

    if ((dir = opendir("./maps")) != nullptr)
    {

        while ((diread = readdir(dir)) != nullptr)
        {
            if (strcmp(diread->d_name, ".") == 0 || strcmp(diread->d_name, "..") == 0)
            {
                continue;
            }
            nameOfMaps.push_back(diread->d_name);
        }
        closedir(dir);
    }
    else
    {
        perror("opendir");
    }
    return nameOfMaps;
}
void GameEngine::startupPhase(CommandProcessor *cp, string choice)
{
    // this is a variable that tracks commands in the command txt file
    int commandTracker = 0;
    
    std::cout << choice << endl;
    vector<string *> commandsOfFile;
    // checking if the choice contains the word file
    if (choice.find("file") == 0)
    {
        // parsing the command to obtain the filename and passing it through the readLineFomLine
        std::stringstream ss(choice);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> tokens(begin, end);
        string CommandFileName = tokens[1];
        FileLineReader *fileCommands = new FileLineReader();
        // getting a vector of all the commands in a file
        commandsOfFile = fileCommands->readLineFromFile(CommandFileName);
    }
    // indicating to the user that the game has started
    std::cout << "**********THE GAME HAS STARTED********** \n"
              << endl;
    std::cout << "Enter the the following command to load a mad (loadmap <filename>): ";
    // creating objects that will be used throughout the function
    string command;
    Map *m = new Map();
    Map *gameMap = new Map();
    string nameMapSaver = "";
    Command *commands;
    // this loop goes through the loadmap and validatemap commands
    while (true)
    {
        MapLoader *loader = new MapLoader();
        vector<string> nameOfMaps;
        nameOfMaps = directory();
        string mapPath = "./maps/";
        string mapthName = "";
        bool truemap = true;
        // displaying to the users the maps he can choose from
        std::cout << "\nHere is a list of maps you can choose from\n";
        int nbr = 0;
        for (auto file : nameOfMaps)
        {
            std::cout << nbr << ": " << file << "\n";
            nbr++;
        }
        // checking if the choice of user was file, if it was then we get the command from the vector of commands
        if (choice.find("file") == 0)
        {
            command = *commandsOfFile[commandTracker];
            commandTracker++;
        }
        // if the user did not choose file we ask the user for his commands through the getCommand() funciton
        else
        {
            commands = cp->getCommand();
            command = commands->command;
        }
        std::cout << "\n";
        // checking if the command contains loadmap
        if (command.find("loadmap") != std::string::npos)
        {
            nameMapSaver = "";
            // checking if the name of the man provided by the user is a valid map
            for (auto name : nameOfMaps)
            {
                if (command.find(name) != std::string::npos)
                {
                    Command *c = new Command(command, "");
                   playegame(c);
                    mapthName = mapPath + name;
                    nameMapSaver = nameMapSaver + name;
                    truemap = true;
                    break;
                }
                else
                {
                    // if the map does not exist then set this variable to false
                    truemap = false;
                }
            }
            // if the truemap is false it means that the map does not exists, then tell the user and change the state to start
            // so that the user cannot validate a non existing map
            if (truemap == false)
            {
                std::cout << "\nInvalid Map name \n";
               setState("start");
            }
            std::cout << "\n";
        }
        // if the command validates the map, then check if we are at the right state
        else if (command == "validatemap" && getState() == "maploaded")
        {
            mapPath = mapPath + nameMapSaver;
            gameMap = loader->loadMap(mapPath);
            // e validate the map
            if (!m->validate(gameMap->territories))
            {
                // if the map is not valid tell the user
                std::cout << "\nInvalid map \n"
                          << endl;
                command = "";
                std::cout << "\nValid commands: loadmap\n " << endl;
               setState("start");
            }
            else
            // if the map is valid change the state
            {
                std::cout << "\n";
                Command *c = new Command(command, "");
               playegame(c);
                command = "";
                break;
            }
        }
        else
        {
            Command *c = new Command(command, "");
           playegame(c);
        }
    }
    std::shuffle(gameMap->territories.begin(), gameMap->territories.end(), std::random_device());
    std::vector<Player *> playersMap;
    while (true)
    {
        std::cout << "\nEnter the next command \n"
                  << endl;

        if (choice.find("file") == 0)
        {
            command = *commandsOfFile[commandTracker];
            commandTracker++;
        }
        else
        {
            commands = cp->getCommand();
            command = commands->command;
        }
        Deck *deck = new Deck();
        if (command.find("addplayer") != std::string::npos)
        {
            Command *c = new Command(command, "");
            playegame(c);
            // parsing the command to get players name
            std::stringstream ss(command);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> tokens(begin, end);
            Player *p = new Player(tokens[1]);
            p->set_armyUnit(50);
            // assigning hands to player
            Hand *hand = new Hand();
            for (int i = 0; i < 2; i++)
            {
                Card *card = deck->draw();
                hand->addCard(card);
            }
            p->set_Player_Hand(hand);
            playersMap.push_back(p);
        }
        else if (command == "gamestart")
        {
            Command *c = new Command(command, "");
            command = "";
            break;
        }
        else
        {
           playegame(commands);
            command = "";
        }
    }

    int count = 0;
    for (auto terr : gameMap->territories)
    {
        if (count == playersMap.size())
        {
            count = 0;
        }
        // adding territories owned territoires to players and adding the corresponding owner to that territory
        vector<Territory *> tempPlayer = playersMap[count]->get_trt();
        tempPlayer.push_back(terr);
        playersMap[count]->set_Trt(tempPlayer);

        terr->territoryOwner = playersMap[count];
        terr->armyAmount = new int(50);

        count++;
    }
    // shuffling the players to get them in random order of paye
    std::shuffle(playersMap.begin(), playersMap.end(), std::random_device());

    // printing the players
    int range = 0;
    for (auto i : playersMap)
    {
        std::cout << "Player " << range << ' ';
        std::cout << "Name: " << ' ';
        std::cout << i->get_name() << ' ';
        std::cout << "ArmyUnit: " << ' ';
        std::cout << i->get_armyUnit() << ' ';
        std::cout << *i->get_Phand() << '\n';
        std::cout << "Territories: " << '\n';
        std::cout << "{" << '\n';
        auto territories = i->get_trt();
        for (auto x : territories)
        {
            std::cout << *x << ',';
        }
        std::cout << "}" << '\n'
                  << endl;
        range++;
    }
    gameMap = gameMap;
    gamePlayers = playersMap;
}
