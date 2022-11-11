

#include "GameEngine.h"
#include "CommandProcessor.h"
#include <iostream>
#include"Player.h"
#include"Cards.h"
#include <string>
using namespace std;

// using std::cin;
// using std::cout;
// using std::endl;
// using std::string;

// void testGameStates() {
//     //creates a pointer to a GameEngine object
//     GameEngine *engine = new GameEngine();
//     //prints out the start message
//     engine->startMessage();
//     //keeps on taking user input as long as the final state has not been reached
//     while (!engine->finished()) {
//         string line;
//         cin>>line;
//         //passes input to the handleInput(string) method to pass through the phases depending on the user's input
//         engine->handleInput(line);
//     }

// }

// void teststartupPhase()
// {
//     // Need implementation
// }
// void testGameStates() {
//     //creates a pointer to a GameEngine object
//     GameEngine *engine = new GameEngine();
//     //prints out the start message
//     engine->startMessage();
//     //keeps on taking user input as long as the final state has not been reached
//     while (!engine->finished()) {
//         string line;
//         cin>>line;
//         //passes input to the handleInput(string) method to pass through the phases depending on the user's input
//         engine->handleInput(line);
//     }

// }
void testGameEngine()
{
    GameEngine *engine = new GameEngine();
    CommandProcessor *cp = new CommandProcessor();
    engine->startupPhase(cp);
}

// void testMainGameLoop()
// {
//     // TODO
//     // Need implementation
//     std::cout << "###" << std::endl;
//     std::cout << "Part 3: Testing Main Game Loop" << std::endl;
//     std::cout << "###\n"
//               << std::endl;
//     GameEngine *gameEngine = new GameEngine();
//     MapLoader *loader = new MapLoader();
//     Map *gameMap = loader->loadMap("./3D.map");
//     vector<Player *> gamePlayers;
//     Player *p1 = new Player("Player1");
//     Player *p2 = new Player("Player2");
//     gamePlayers.push_back(p1);
//     gamePlayers.push_back(p2);

//     // assign territories to player
//     vector<Territory *> p1_trt;
//     vector<Territory *> p2_trt;
//     for (int i = 0; i < 5; i++)
//     {
//         Territory *t = gameMap->territories.at(i);
//         p1_trt.push_back(t);
//     }
//     for (int i = 5; i < gameMap->territories.size(); i++)
//     {
//         Territory *t = gameMap->territories.at(i);
//         p2_trt.push_back(t);
//     }
//     p1->set_Trt(p1_trt);
//     p1->set_armyUnit(50);
//     p2->set_Trt(p2_trt);
//     p2->set_armyUnit(50);

//     std::cout << "Player1 owns:" << std::endl;
//     for (Territory *t : p1_trt)
//     {
//         std::cout << *(t->getTerritoryName)() << "\t";
//     }
//     std::cout << "\n";
//     std::cout << "Player2 owns:" << std::endl;
//     for (Territory *t : p2_trt)
//     {
//         std::cout << *(t->getTerritoryName)() << "\t";
//     }
//     std::cout << "\n\n##Starting Main Game Loop##\n\n";
//     gameEngine->setMap(gameMap);
//     gameEngine->setPlayers(gamePlayers);

//     bool finished = false;
//     while (!finished)
//     {
//         finished = gameEngine->mainGameLoop(gamePlayers, gameMap);
//     }
// }
void testMainGameLoop(){

    std::cout<<"###"<<std::endl;
    std::cout<<"Part 3: Testing Main Game Loop"<<std::endl;
    std::cout<<"###\n"<<std::endl;

    //Prepare game play
    GameEngine* gameEngine = new GameEngine();
    gameEngine->setState("start");
    MapLoader* loader = new MapLoader();
    Map* gameMap = loader->loadMap("./3D.map");
    //change state from 'start' to 'maploaded'
    gameEngine->transition();
    //change state from 'maploaded' to 'mapvalidated'
    gameEngine->transition();
    vector <Player*> gamePlayers;
    Player* p1 = new Player("Player1");
    Player* p2 = new Player("Player2");
    gamePlayers.push_back(p1);
    gamePlayers.push_back(p2);

    //assign 2 cards from deck to players
    Deck* d = new Deck();
    Hand* h1= new Hand();
    for (int i = 0; i < 2; i++) {
        h1->addCard(d->draw());
    }
    Hand* h2= new Hand();
    for (int i = 0; i < 2; i++) {
        h2->addCard(d->draw());
    }
    p1->set_Player_Hand(h1);
    p2->set_Player_Hand(h2);

    //assign territories to player
    vector <Territory*> p1_trt;
    vector <Territory*> p2_trt;
    for(int i=0; i<3; i++){
        Territory* t = gameMap->territories.at(i);
        t -> setTerritoryOwner(p1);
        p1_trt.push_back(t);
    }
    for(int i=5; i<gameMap->territories.size(); i++){
        Territory* t = gameMap->territories.at(i);
        t -> setTerritoryOwner(p2);
        p2_trt.push_back(t);
    }
    p1->set_Trt(p1_trt);
    p1->set_armyUnit(50);
    p2->set_Trt(p2_trt);
    p2->set_armyUnit(50);

    //change state from 'mapvalidated' to 'playersadded'
    gameEngine->transition();

    std::cout<< "Player1 owns:" << std::endl;
    for (Territory* t: p1_trt){
        std::cout << *(t->getTerritoryName)() << "\t";
    }
    std::cout<<"\nPlayer1's hand of cards:\n";
    std::cout<<*h1;
    std::cout<<"\n";
    std::cout<< "\nPlayer2 owns:" << std::endl;
    for (Territory* t: p2_trt){
        std::cout << *(t->getTerritoryName)() << "\t";
    }
    std::cout<<"\nPlayer2's hand of cards:\n";
    std::cout<<*h2;

    std::cout<<"\n\n##Starting Main Game Loop##\n\n";
    gameEngine->setMap(gameMap);
    gameEngine->setPlayers(gamePlayers);

    bool finished = false;
    while(!finished){
        finished = gameEngine->mainGameLoop(gamePlayers, gameMap);
    }
    //change state from 'mapvalidated' to 'playersadded'
    gameEngine->setState("quit");
    gameEngine->transition();
    
}
