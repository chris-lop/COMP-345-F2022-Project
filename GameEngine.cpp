#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <cstring>
#include <dirent.h>
#include <random>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;

// GameEngine class
// start message
void GameEngine::startMessage()
{
    cout << "Now in start state. Valid input: loadmap" << endl;
}

// constructor and destructor
GameEngine::GameEngine() : state(0)
{
}

// GameEngine destructor
GameEngine::~GameEngine()
{
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

// setters and getters
void GameEngine::setState(int st)
{
    state = st;
}
// getter for state
int GameEngine::getState()
{
    return state;
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
    // continentsList = map STL with <continent_name, bonus_value>
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
void GameEngine::issueOrdersPhase(Player *p)
{

    vector<Territory *> trt_attack = p->toAttack();
    vector<Territory *> trt_defend = p->toDefend();

    // Notify player of the current list of territories to defend and to attack
    std::cout << "Issue orders for " << p->get_name() << std::endl;
    std::cout << "Player's territories to defend: " << std::endl;
    for (Territory *t : trt_defend)
    {
        std::cout << *(t->getTerritoryName()) << " ";
    }
    std::cout << std::endl;
    std::cout << "Player's territories to attack: " << std::endl;
    for (Territory *t : trt_attack)
    {
        std::cout << *(t->getTerritoryName()) << " ";
    }
    std::cout << std::endl;

    // Issue deploy order
    bool deploy = true;
    bool issue = true;
    int i_count = 0;
    while (deploy)
    {
        if (p->get_armyUnit() > 0)
        {
            std::string answer;
            std::cout << "Issue Deploy order? (Y/N)" << std::endl;
            std::cin >> answer;
            if (answer == "Y")
            {
                int army;
                std::cout << "Deploying army units to " << trt_defend.at(i_count)->getTerritoryName() << std::endl;
                std::cout << "Number of army units to deploy: ";
                std::cin >> army;
                Deploy *d = new Deploy(trt_defend.at(i_count), trt_defend.at(i_count)->getTerritoryOwner(), army);
                p->issueOrder(d);
                i_count += 1;
            }
            else if (answer == "N")
            {
                std::cout << "You cannot issue other orders if you don't deploy all army units." << endl;
                std::cout << "Moving on to the next player." << endl;
                deploy = false;
                issue = false;
            }
            else
            {
                std::cout << "Please enter the correct answer." << std::endl;
            }
        }
        // player does not have any more army units
        else
        {
            std::cout << "You don't have any more army units to deploy." << endl;
            deploy = false;
        }
    }

    // If no more army units, proceed to issue other orders
    // If player has army units left undeployed, then this while loop will be skipped
    while (issue)
    {
        bool yn = true;
        while (yn)
        {
            std::string answer;
            std::cout << "Add more order? (Y/N)" << std::endl;
            std::cin >> answer;
            if (answer == "Y")
            {
                issue = true;
                yn = true;
                // TODO
                // issueOrders() need following corrections: remove deploy() as option, use the correct constructor for each order type
                Order *o = issueOrders(); // issueOrders() of GameEngine class to prompt user to select orders
                p->issueOrder(o);
            }
            else if (answer == "N")
            {
                issue = false;
                yn = false;
            }
            else
            {
                std::cout << "Please enter the correct answer." << std::endl;
                yn = true;
            }
        }
    }
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
        std::cout << "Player " << winPlayer << " conquered all territories of the map and won the game.";
        finished = true;
    }

    else
    {

        // Phase 1: Reinforcement --> call reinforcementPhase() in round-robin
        for (Player *p : players)
        {
            assignReinforcement();
            reinforcementPhase(p, graph);
        }

        // Phase 2: issue Orders --> call issueOrdersPhase() in round-robin
        for (Player *p : players)
        {
            issueOrdersPhase(p);
        }

        // Phase 3: execute Orders --> call executeOrdersPhase() in round-robin
    }

    return finished;
}

void GameEngine::startupPhase()
{
    while (true)
    {
        char input[100];
        cout << "Would you like to start the Game? [y/n] " << endl;
        cin >> input;
        if (strcmp(input, "y") == 0)
        {
            cout << "Here is a list of map you can choose from" << endl;
            break;
        }
        else if (strcmp(input, "n") == 0)
        {
            cout << "You have exited" << endl;
            exit(0);
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }
    DIR *dir;
    struct dirent *diread;
    vector<char *> nameOfMaps;
    char buffer[1000];
    char *answer = getcwd(buffer, sizeof(buffer));

    char *path = new char[std::strlen(answer) + std::strlen("/maps") + 1];
    std::strcat(path, answer);
    std::strcat(path, "/maps");

    std::cout << path << endl;

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

    int count = 0;

    // Allow user to chose map to play on
    int mapSelector;
    Map *m = new Map();
    Map *gameMap = new Map();
    MapLoader *loader = new MapLoader();
    while (true)
    {
        int nbr = 0;
        for (auto file : nameOfMaps)
        {

            cout << nbr << ": " << file << "\n";
            nbr++;
        }
        cout << endl;
        mapSelector = 0;
        cout << "Enter the number that corresponds to the map you want to play on" << endl;
        cin >> mapSelector;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Map does not exists" << endl;
            continue;
        }
        if (mapSelector > nameOfMaps.size() - 1 || mapSelector < 0)
        {
            cout << "Map does not exists" << endl;
            continue;
        }
        char mapPath[1000] = "./maps/";
        strcat(mapPath, nameOfMaps[mapSelector]);
        cout << mapPath << endl;

        // Map *m = new Map();
        // Map *gameMap = new Map();
        // MapLoader *loader = new MapLoader();
        gameMap = loader->loadMap(mapPath);

        if (!m->validate(gameMap->territories))
        {
            cout << " \nInvalid map \n"
                 << endl;
            cout << "Please make another choice \n"
                 << endl;
            continue;
        }
        // Validate the map
        // m->validate(gameMap->territories);
        break;
    }

    // add players
    int players = 0;
    while (true)
    {
        // fix infinite loop
        cout << "Enter the number of players that will play the game [2-6]" << endl;
        cin >> players;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Number" << endl;
            continue;
        }
        if (players < 2 || players > 6)
        {
            cout << "Invalid number of players" << endl;
            continue;
        }
        break;
    }
    // creating deck to assign it all to players
    Deck *deck = new Deck();

    // creating the players and adding them to the player vector
    std::vector<Player *> playersMap;
    for (int i = 0; i < players; i++)
    {
        cout << "Enter player " << i << "'s name" << endl;
        string name;
        cin >> name;
        Player *p = new Player(name);
        p->set_armyUnit(50);

        // setting 2 cards per player
        Hand *hand = new Hand();
        for (int i = 0; i < 2; i++)
        {
            Card *card = deck->draw();
            hand->addCard(card);
        }

        p->set_Player_Hand(hand);
        playersMap.push_back(p);
    }

    // fairly distribute players and give 50 initial army units
    count = 0;
    for (auto terr : gameMap->territories)
    {
        if (count == players)
        {
            count = 0;
        }
        // adding territories owned territoires to players and adding the corresponding owner to that territory
        vector<Territory *> tempPlayer = playersMap[count]->get_trt();
        tempPlayer.push_back(terr);
        playersMap[count]->set_Trt(tempPlayer);

        terr->territoryOwner = playersMap[count];

        count++;
    }
    // randomize the players
    std::shuffle(playersMap.begin(), playersMap.end(), std::random_device());

    int range = 0;
    // printing the players
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
    mainGameLoop(playersMap, gameMap);
}
