
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"

void testStatUpPhase(string commandChoice)
{
    std::cout << "###" << std::endl;
    std::cout << "Part 2: Testing Stat UP Phase" << std::endl;
    std::cout << "###\n"
              << std::endl;
    GameEngine *engine = new GameEngine();
    CommandProcessor *cp = new CommandProcessor();
    engine->startupPhase(cp, commandChoice);
}

void testMainGameLoop()
{

    std::cout << "###" << std::endl;
    std::cout << "Part 3: Testing Main Game Loop" << std::endl;
    std::cout << "###\n"
              << std::endl;

    // Prepare game play
    GameEngine *gameEngine = new GameEngine();
    gameEngine->setState("start");
    MapLoader *loader = new MapLoader();
    Map *gameMap = loader->loadMap("./maps/3D.map");
    // change state from 'start' to 'maploaded'
    gameEngine->transition();
    // change state from 'maploaded' to 'mapvalidated'
    gameEngine->transition();
    vector<Player *> gamePlayers;
    vector<Player *> removedPlayers;
    Player *p1 = new Player("Player1");
    Player *p2 = new Player("Player2");

    gamePlayers.push_back(p1);
    gamePlayers.push_back(p2);

    // assign 2 cards from deck to players
    Deck *d = new Deck();
    gameEngine->setDeck(d);
    Hand *h1 = new Hand();
    for (int i = 0; i < 2; i++)
    {
        h1->addCard(d->draw());
    }
    Hand *h2 = new Hand();
    for (int i = 0; i < 2; i++)
    {
        h2->addCard(d->draw());
    }

    p1->set_Player_Hand(h1);
    p2->set_Player_Hand(h2);

    // assign territories to player
    vector<Territory *> p1_trt;
    vector<Territory *> p2_trt;

    // assign random number of territories each time
    int rdm_trt_num = 1 + (rand() % (gameMap->territories.size() - 1));
    for (int i = 0; i < rdm_trt_num; i++)
    {
        Territory *t = gameMap->territories.at(i);
        t->setTerritoryOwner(p1);
        p1_trt.push_back(t);
    }
    // gameMap->territories.size()
    for (int i = rdm_trt_num; i < gameMap->territories.size(); i++)
    {
        Territory *t = gameMap->territories.at(i);
        t->setTerritoryOwner(p2);
        p2_trt.push_back(t);
    }

    p1->set_Trt(p1_trt);
    p1->set_armyUnit(50);
    p2->set_Trt(p2_trt);
    p2->set_armyUnit(50);

    // change state from 'mapvalidated' to 'playersadded'
    gameEngine->transition();

    std::cout << "Player1 owns:" << std::endl;
    for (Territory *t : p1_trt)
    {
        std::cout << *(t->getTerritoryName)() << "\t";
    }
    std::cout << "\nPlayer1's hand of cards:\n";
    std::cout << *h1;
    std::cout << "\n";
    std::cout << "\nPlayer2 owns:" << std::endl;
    for (Territory *t : p2_trt)
    {
        std::cout << *(t->getTerritoryName)() << "\t";
    }
    std::cout << "\nPlayer2's hand of cards:\n";
    std::cout << *h2;

    std::cout << "\n\n##Starting Main Game Loop##\n\n";
    gameEngine->setMap(gameMap);
    gameEngine->setPlayers(gamePlayers);
    gameEngine->setRemovedPlayers(removedPlayers);

    bool finished = false;
    while (!finished)
    {
        finished = gameEngine->mainGameLoop(gamePlayers, gameMap,0);
    }
    // change state from 'win' to 'quit'
    gameEngine->setState("quit");
    gameEngine->transition(); 
}
