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
    cout << "Now in start state. Valid input: loadmap" << endl;
}

// Default Constructor
GameEngine::GameEngine() : state(0)
{
    this->state = 0;
    this->gameMap = new Map();
    this->gamePlayers = {};
    this->removedPlayers = {};
}

GameEngine::GameEngine(Map *gameMap, vector<Player *> gamePlayers)
{
    this->state = 0;
    this->gameMap = gameMap;
    this->gamePlayers = gamePlayers;
    this->removedPlayers = {};
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
void GameEngine::setState(int st)
{
    this->state = st;
}

void GameEngine::setMap(Map *gameMap)
{
    this->gameMap = gameMap;
}

void GameEngine::setPlayers(vector<Player *> gamePlayers)
{
    this->gamePlayers = gamePlayers;
}

// getters
int GameEngine::getState()
{
    return state;
}

Map *GameEngine::getMap()
{
    return this->gameMap;
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
    cout << "Loading map..." << endl;
}

// validates the map, prints out that the map got validated
void GameEngine::validateMap()
{
    cout << "Validating map..." << endl;
}

// takes player's name as input from the user and creates a player
void GameEngine::addPlayers()
{
    string name;
    cout << "enter the name of the palyer." << endl;
    cin >> name;
    Player *p = new Player(name);
    cout << *p;
    delete p;
}

// prints out assigning reinforcement
void GameEngine::assignReinforcement()
{
    cout << "assigning reinforcements..." << endl;
}

// takes user's input and creates an order depending on input
Order *GameEngine::issueOrders()
{
    string type;
    Order *order = nullptr;
    do
    {
        cout << "enter your order." << endl;
        cin >> type;
        if (type != "bomb" && type != "blockade" && type != "airlift" && type != "negotiate" && type != "deploy" && type != "advance")
            cout << "invalid type. valid types: bomb, bloackade, airlift, negotiate, deploy, advance." << endl;
        if (type == "bomb")
        {
            order = new Bomb();
        }
        else if (type == "blockade")
        {
            order = new Blockade();
        }
        else if (type == "airlift")
        {
            order = new Airlift();
        }
        else if (type == "negotiate")
        {
            order = new Negotiate();
        }
        else if (type == "deploy")
        {
            order = new Deploy();
        }
        else if (type == "advance")
        {
            order = new Advance();
        }
        if (order != nullptr)
        {
            cout << *order << endl;
        }
        delete order;
    } while (type != "bomb" && type != "blockade" && type != "airlift" && type != "negotiate" && type != "deploy" && type != "advance");

    return order;
}

// executes orders, prints out executing orders
void GameEngine::executeOrders()
{
    cout << "executing orders..." << endl;
}

// prints out you win
void GameEngine::win()
{
    cout << "you win." << endl;
}

// moves through the states depending on the user's command which will be passed to the function as a parameter
void GameEngine::handleInput(std::string line)
{
    if (state == 0)
    {
        // State: start
        // valid inputs: loadmap
        if (line == "loadmap")
        {
            loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = 1;
        }
        else
        {
            cout << "Invalid command. Valid commands: loadmap" << endl;
        }
    }
    else if (state == 1)
    {
        // State: map loaded
        // Valid inputs: loadmap, validatemap
        if (line == "loadmap")
        {
            loadMap();
            cout << "Now in map loaded state. Valid input: loadmap, validatemap" << endl;
            state = 1;
        }
        else if (line == "validatemap")
        {
            validateMap();
            cout << "Map now validated, you are in validated state. Valid input: addplayer" << endl;
            state = 2;
        }
        else
        {
            cout << "Invalid command. Valid commands: loadmap, validatemap." << endl;
        }
    }
    else if (state == 2)
    {
        // State: map validated
        // Valid input: addplayer
        if (line == "addplayer")
        {
            addPlayers();
            cout << "you are now in players added state. Valid input: addplayer, assigncountries." << endl;

            state = 3;
        }
        else
        {
            cout << "Invalid command. Valid command: addplayer" << endl;
        }
    }
    // players added state
    else if (state == 3)
    {
        // state: players added
        // valid input: addplayer, assigncountries
        if (line == "addplayer")
        {
            addPlayers();
            cout << "you are now in players added state. Valid input: addplayer, assigncountries." << endl;

            state = 3;
        }
        else if (line == "assigncountries")
        {
            assignReinforcement();
            cout << "you are now in assign reinforcement state. Valid input: issueorder." << endl;

            state = 4;
        }
        else
            cout << "Invalid command. Valid commands: addplayer, assigncountries." << endl;
    }
    else
        // the issue orders state
        if (state == 4)
        {
            // state assign reinforcement
            // valid input: issueorder
            if (line == "issueorder")
            {
                issueOrders();
                cout << "you are now in the issue orders state. Valid input: issueorder, endissueorders." << endl;

                state = 5;
            }
            else
                cout << "Invalid command. Valid command: issueorder. " << endl;
        }
        else
            // the issue orders state
            if (state == 5)
            {
                if (line == "issueorder")
                {
                    issueOrders();
                    cout << "you are now in the issue orders state. Valid input: issueorder, endissueorders." << endl;

                    state = 5;
                }
                else
                    // the execute orders state
                    if (line == "endissueorders")
                    {
                        executeOrders();
                        cout << "You are now in the execute orders state. Valid input: execorder, endexecorders, win." << endl;
                        state = 6;
                    }

                    else
                    {
                        cout << "Invalid input. valid commands: issueorder, endissueorders." << endl;
                    }
            }
            else
                // the execute orders state
                if (state == 6)
                {
                    if (line == "execorder")
                    {
                        executeOrders();
                        cout << "you are now in the execute orders state. valid input: execorder, endexecorders, win." << endl;
                        state = 6;
                    }
                    else
                        // assign reinforcement state
                        if (line == "endexecorders")
                        {
                            assignReinforcement();
                            cout << "you are now in assign reinforcement state. Valid input: issueorder." << endl;

                            state = 4;
                        }
                        else
                            // the win state
                            if (line == "win")
                            {
                                win();
                                cout << "you are now in the win state. valid input: end, play." << endl;
                                state = 7;
                            }
                            else
                            {
                                cout << "invalid command. valid input: execorder, endexecorders, win." << endl;
                            }
                }
                else
                    // pplay again or end the game
                    if (state == 7)
                    {
                        if (line == "play")
                        {

                            startMessage();
                            state = 0;
                        }
                        else if (line == "end")
                        {
                            cout << "Game finishing..." << endl;
                            state = 8;
                        }
                        else
                            cout << "Invalid command. valid commands: play, end." << endl;
                    }
}

// checks whether the final state has been reached or not
bool GameEngine::finished()
{
    return state == 8;
}

// A2 functions
// reinforcementPhase(): provide each players with the appropriate army units number
void GameEngine::reinforcementPhase(Player *p, Map *graph)
{
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
            p->set_armyUnit(p->get_armyUnit() + bonus);
        }
        // else, continue the verification with the next continent
        else
        {
            continue;
        }
    }

    std::cout << "Player " << p->get_name() << "'s total army units: " << p->get_armyUnit() << std::endl;
}

// issueOrdersPhase(): each player issue orders
void GameEngine::issueOrdersPhase(vector<Player *> players)
{
    int pool[players.size()];
    for (int i = 0; i < players.size(); i++)
    {
        pool[i] = 0;
    }
    bool deploy[players.size()];
    for (int i = 0; i < players.size(); i++)
    {
        deploy[i] = false;
    }
    bool done[players.size()];
    for (int i = 0; i < players.size(); i++)
    {
        done[i] = false;
    }

    for (Player *p : players)
    {
        // Notify player of the current list of territories to defend and to attack
        vector<Territory *> trt_attack = p->toAttack();
        vector<Territory *> trt_defend = p->toDefend();
        std::cout << "Player " << p->get_name() << "'s territories to defend: " << std::endl;
        for (Territory *t : trt_defend)
        {
            std::cout << *(t->getTerritoryName()) << " ";
        }
        std::cout << "\n";
        std::cout << "Player" << p->get_name() << "'s territories to attack: " << std::endl;
        for (Territory *t : trt_attack)
        {
            std::cout << *(t->getTerritoryName()) << " ";
        }
        std::cout << "\n\n";
    }

    bool issue = true;
    while (issue)
    {
        for (int i = 0; i < players.size(); i++)
        {

            if (done[i] == true)
            {
                std::cout << "Player " << players.at(i)->get_name() << " finished issuing orders.\n"
                          << std::endl;
                continue;
            }
            else
            {
                std::cout << "Issuing order for player " << players.at(i)->get_name() << std::endl;
                // every turn, check if the current player finished deploying army
                // if yes, skip to next issue order
                if (pool[i] == players.at(i)->get_armyUnit())
                {
                    deploy[i] = true;
                    std::cout << "You deployed all your army units.\n\n";
                }
                else
                {
                    std::cout << "You have army units in your reinforcement pool.\nYou can only issue deploy order.\n";
                    std::cout << "Current army units in the pool: " << (players.at(i)->get_armyUnit() - (pool[i])) << std::endl;
                    bool yn = true;
                    std::string answer;
                    std::cout << "Issue deploy order? (Y/N)\n";
                    std::cin >> answer;
                    while (yn)
                    {
                        // Issue deploy order
                        if (answer == "Y" || answer == "y")
                        {
                            int army;
                            vector<Territory *> trt_defend = players.at(i)->toDefend();
                            int limit = trt_defend.size();
                            int rdm_i = rand() % limit;
                            std::cout << "Deploying army units to " << *(trt_defend.at(rdm_i)->getTerritoryName()) << std::endl;
                            std::cout << "Number of army units to deploy: ";
                            std::cin >> army;
                            Deploy *d = new Deploy(trt_defend.at(rdm_i), trt_defend.at(rdm_i)->getTerritoryOwner(), army);
                            players.at(i)->issueOrder(d);
                            pool[i] = pool[i] + army;
                            yn = false;
                        }
                        // If player does not wish to issue deploy order
                        else if (answer == "N" || answer == "n")
                        {
                            std::cout << "Player cannot issue more orders without deploying all army units.\nPlayer's turn will be skipped.\n\n";
                            done[i] = true;
                            yn = false;
                        }
                        else
                        {
                            std::cout << "!ERROR!***Please enter the correct answer.***" << std::endl;
                            yn = true;
                        }
                    }
                }
            } // end of else

            // issue other orders
            if (done[i] == false && deploy[i] == true)
            {
                bool yn = true;
                std::string answer;
                std::cout << "Issue other orders? (Y/N)\n";
                std::cin >> answer;
                while (yn)
                {
                    if (answer == "Y" || answer == "y")
                    {
                        // TODO
                        // issueOrders() need following corrections: remove deploy() as option, use the correct constructor for each order type
                        Order *o = issueOrders(); // issueOrders() of GameEngine class to prompt user to select orders
                        players.at(i)->issueOrder(o);
                        yn = false;
                    }
                    else if (answer == "N" || answer == "n")
                    {
                        done[i] = true;
                        yn = false;
                    }
                    else
                    {
                        std::cout << "!ERROR!***Please enter the correct answer.***" << std::endl;
                        yn = true;
                    }
                }
            }

        } // end of for

        // verify all players have completed issuing orders
        int count = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (done[i] == true)
            {
                count = count + 1;
            }
        }
        if (count == players.size())
        {
            issue = false;
        }
    } // end of while
}

// TODO
// executeOrdersPhase(): execute the top order on the list of orders of each player
void executeOrdersPhase()
{
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
            std::cout << "\nCurrent turn: " << p->get_name() << std::endl;
            reinforcementPhase(p, graph);
        }
        std::cout << "\n<<<reinforcement phase complete...>>>\n";

        // Phase 2: issue Orders --> call issueOrdersPhase() in round-robin
        std::cout << "\n#issueing orders...\n";
        issueOrdersPhase(gamePlayers);
        std::cout << "\n<<<issue order phase complete>>>\n";

        // to test if everything's working
        // TO REMOVE when Phase 3 is complete
        finished = true;

        // Phase 3: execute Orders --> call executeOrdersPhase() in round-robin
    }

    return finished;
}

vector<char *> GameEngine::directory()
{
    DIR *dir;
    struct dirent *diread;
    vector<char *> nameOfMaps;
    char buffer[1000];
    char *answer = getcwd(buffer, sizeof(buffer));

    char *path = new char[std::strlen(answer) + std::strlen("/maps") + 1];
    std::strcat(path, answer);
    std::strcat(path, "/maps");

    if ((dir = opendir(path)) != nullptr)
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
void GameEngine::startupPhase(CommandProcessor *cp)
{

    cout << "**********THE GAME HAS STARTED********** \n"
         << endl;
    cout << "Enter the the following command to load a mad (loadmap <filename>): ";
    string command;
    Map *m = new Map();
    Map *gameMap = new Map();
    MapLoader *loader = new MapLoader();
    char nameMapSaver[1000] = "";
    while (true)
    {
        vector<char *> nameOfMaps;
        nameOfMaps = directory();
        char mapPath[1000] = "./maps/";
        bool truemap = true;
        cout << "\nHere is a list of maps you can choose from\n";
        int nbr = 0;
        for (auto file : nameOfMaps)
        {
            cout << nbr << ": " << file << "\n";
            nbr++;
        }
        getline(cin, command);
        cout << "\n";
        if (command.find("loadmap") != std::string::npos)
        {
            nameMapSaver[0] = 0;
            cp->saveCommand(command);
            for (auto name : nameOfMaps)
            {
                if (command.find(name) != std::string::npos)
                {
                    cp->playegame(command);
                    strcat(mapPath, name);
                    strcat(nameMapSaver, name);
                    truemap = true;
                    break;
                }
                else
                {
                    truemap = false;
                }
            }
            if (truemap == false)
            {
                cout << "\nInvalid Map name \n";
                cp->set_state("start");
            }
            cout << "\n";
        }
        else if (command == "validatemap" && cp->get_state() == "maploaded")
        {
            cout << cp->get_state() << endl;
            cp->saveCommand(command);
            strcat(mapPath, nameMapSaver);
            gameMap = loader->loadMap(mapPath);
            if (!m->validate(gameMap->territories))
            {
                cout << " \nInvalid map \n"
                     << endl;
                command = "";
                cout << "\nValid commands: loadmap\n " << endl;
                cp->set_state("start");
            }
            else
            {
                cout << "\n";
                cp->playegame(command);
                cp->saveCommand(command);
                command = "";
                break;
            }
        }
        else
        {
            cp->playegame(command);
        }
    }
    std::shuffle(gameMap->territories.begin(), gameMap->territories.end(), std::random_device());
    std::vector<Player *> playersMap;
    while (true)
    {
        cout << "\nEnter the next command \n"
             << endl;
        getline(cin, command);
        Deck *deck = new Deck();
        if (command.find("addplayer") != std::string::npos)
        {
            cp->playegame(command);
            cp->saveCommand(command);
            string nameOfPlayer;

            std::stringstream ss(command);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> tokens(begin, end);
            Player *p = new Player(tokens[1]);
            cout << tokens[1] << "TOKEN";
            p->set_armyUnit(50);
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
            cp->saveCommand(command);
            command = "";
            break;
        }
        else
        {
            command = "";
            cp->playegame(command);
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
