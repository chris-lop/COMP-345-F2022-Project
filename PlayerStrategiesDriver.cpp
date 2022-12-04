#include "PlayerStrategy.h"
#include "Cards.h"
#include "GameEngine.h"

void runGameLoop(Player* p1, Player* p2);
void runGameLoopHuman(Player* p1, Player* p2);

void testPlayerStrategies()
{
    // Setting up sample game
    Territory *territory1 = new Territory(new string("territory1"), new string("continent1"), vector<Territory*>{}, nullptr, new int(1));
    Territory *territory2 = new Territory(new string("territory2"), new string("continent1"), vector<Territory*>{}, nullptr, new int(4));
    Territory *territory3 = new Territory(new string("territory3"), new string("continent1"), vector<Territory*>{}, nullptr, new int(2));
    Territory *territory4 = new Territory(new string("territory4"), new string("continent1"), vector<Territory*>{}, nullptr, new int(3));
    territory1->setAdjTerritories(std::vector<Territory*> {territory2});
    territory2->setAdjTerritories(std::vector<Territory*> {territory1, territory3, territory4});
    territory3->setAdjTerritories(std::vector<Territory*> {territory2});
    territory4->setAdjTerritories(std::vector<Territory*> {territory2});
    Player *player1 = new Player("Chris", {territory1, territory2, territory3}, NULL, new OrdersList(), 0);
    Player *player2 = new Player("Marc", {territory4}, NULL, new OrdersList(), 0);
    territory1->setTerritoryOwner(player1);
    territory2->setTerritoryOwner(player1);
    territory3->setTerritoryOwner(player1);
    territory4->setTerritoryOwner(player2);
    // assign 2 to players
    Hand *h1 = new Hand();
    h1->addCard(new Card("Airlift"));
    h1->addCard(new Card("Bomb"));
    Hand *h2 = new Hand();

    player1->set_Player_Hand(h1);
    player2->set_Player_Hand(h2);

    // Create Player Strategies
    NeutralPlayerStrategy* neutralp1 = new NeutralPlayerStrategy(player2);
    AggressivePlayerStrategy* aggrp1 = new AggressivePlayerStrategy(player1);

    // Change Player Strategies
    player1->set_strategy(aggrp1);
    player2->set_strategy(neutralp1);

    cout << "##################################################################" << endl;
    cout << "#### Testing the aggressive player against the neutral player ####" << endl;
    cout << "##################################################################" << endl;

    // While player1 hasn't won
    while (player1->get_trt().size() != 4)
    {
        cout << "TURN BEGINNING" << endl;

        // Player 1 issues orders
        player1->issueOrder();

        // Player 1 execute orders
        vector<Order*> p1_olist = player1->get_olst()->getOrder();

        // Execute all orders in order list
        cout << "Executing Orders..." << endl;
        while (p1_olist.size() != 0)
        {
            // Execute and remove player order
            p1_olist[0]->execute();
            p1_olist.erase(p1_olist.begin());

            OrdersList* new_olst = player1->get_olst();
            new_olst->setOrder(p1_olist);

            // Remove card from player hand
            vector<Card*> p1_hand = player1->get_Phand()->cardList();

            for (int i = 0; i < p1_hand.size() ; i++)
            {
                if (p1_hand[i]->getType() == p1_olist[0]->getType())
                {
                    p1_hand.erase(p1_hand.begin()+i);
                }
            }

            Hand* newHand = new Hand();
            newHand->setCards(p1_hand);
            player1->set_Player_Hand(newHand);
        }

        cout << endl;
        cout << "END OF THIS TURN" << endl;
        cout << "-----------------------------------" << endl;
    }
    if (player1->get_trt().size() == 4)
    {
        cout << "\nPlayer 1 has conquered all the territories and won the game!\n\n";
    }
    delete player1; delete player2;

    cout << "##################################################################" << endl;
    cout << "#### Testing the cheater player against the Aggressive player ####" << endl;
    cout << "##################################################################" << endl;
    
    player1 = new Player("Marc");
    player2 = new Player("William");
    PlayerStrategy *ps1 = new CheaterPlayerStrategy(player1);
    PlayerStrategy *ps2 = new AggressivePlayerStrategy(player2);
    player1->set_strategy(ps1);
    player2->set_strategy(ps2);
    runGameLoop(player1, player2);


    cout << "##################################################################" << endl;
    cout << "#### Testing the human player against the Benevolent player ####" << endl;
    cout << "##################################################################" << endl;

    Player* playerh = new Player("Human");
    Player* playerb = new Player("Benevolent");
    PlayerStrategy *psb = new BenevolentPlayerStrategy(playerb);
    PlayerStrategy *psh = new HumanPlayerStrategy(playerh);
    playerb->set_strategy(psb);
    playerh->set_strategy(psh);
    runGameLoopHuman(playerb, playerh);
}

void runGameLoop(Player* p1, Player* p2) {
    // Prepare game play
    GameEngine *gameEngine = new GameEngine();
    gameEngine->setState("start");
    MapLoader *loader = new MapLoader();
    Map *gameMap = loader->loadMap("./maps/3D.map");
    // change state from 'start' to 'maploaded'
    gameEngine->setState("maploaded");
    // change state from 'maploaded' to 'mapvalidated'
    gameEngine->setState("mapValidated");
    vector<Player *> gamePlayers;
    vector<Player *> removedPlayers;
    // Players are given in function arguments
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
    gameEngine->setState("playersadded");

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
        finished = gameEngine->mainGameLoop(gamePlayers, gameMap, 0);
    }
    // change state from 'win' to 'quit'
    gameEngine->setState("quit");
}


void runGameLoopHuman(Player* p1, Player* p2) {
    // Prepare game play
    GameEngine *gameEngine = new GameEngine();
    gameEngine->setState("start");
    MapLoader *loader = new MapLoader();
    Map *gameMap = loader->loadMap("./maps/3D.map");
    // change state from 'start' to 'maploaded'
    gameEngine->setState("maploaded");
    // change state from 'maploaded' to 'mapvalidated'
    gameEngine->setState("mapValidated");
    vector<Player *> gamePlayers;
    vector<Player *> removedPlayers;
    // Players are given in function arguments
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
    h2->addCard(new Card("Airlift"));
    h2->addCard(new Card("Bomb"));
    
    p1->set_Player_Hand(h1);
    p2->set_Player_Hand(h2);

    // assign territories to player
    vector<Territory *> p1_trt;
    vector<Territory *> p2_trt;

    // assign random number of territories each time
    for (int i = 0; i < 2; i++)
    {
        Territory *t = gameMap->territories.at(i);
        t->setTerritoryOwner(p1);
        p1_trt.push_back(t);
    }
    // gameMap->territories.size()
    for (int i = 2; i < gameMap->territories.size(); i++)
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
    gameEngine->setState("playersadded");

    std::cout << "Player1 owns:" << std::endl;
    for (Territory *t : p1_trt)
    {
        std::cout << *t->getTerritoryName() << "\t";
    }
    std::cout << "\nPlayer1's hand of cards:\n";
    std::cout << *h1;
    std::cout << "\n";
    std::cout << "\nPlayer2 owns:" << std::endl;
    for (Territory *t : p2->get_trt())
    {
        std::cout << *t->getTerritoryName() << "\t";
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
        finished = gameEngine->mainGameLoop(gamePlayers, gameMap, 0);
    }
    // change state from 'win' to 'quit'
    gameEngine->setState("quit");
}