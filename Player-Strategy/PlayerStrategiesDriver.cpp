#include "PlayerStrategy.h"
#include "../Cards.h"

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
    Hand *h2 = new Hand();
    h2->addCard(new Card("Bomb"));

    player1->set_Player_Hand(h1);
    player2->set_Player_Hand(h2);

    // Create Player Strategies
    NeutralPlayerStrategy* neutralp1 = new NeutralPlayerStrategy(player2);
    AggressivePlayerStrategy* aggrp1 = new AggressivePlayerStrategy(player1);

    // Change Player Strategies
    player1->set_strategy(aggrp1);
    player2->set_strategy(neutralp1);

    // While player1 hasn't won
    while (player1->get_trt().size() != 4)
    {
        // Player 1 issues orders
        player1->issueOrder();

        // Player 1 execute orders
        vector<Order*> p1_olist = player1->get_olst()->getOrder();

        // Execute all orders in order list
        for (auto it : p1_olist)
        {
            it->execute();
        }

        // Print territory 4
        cout << "Territory 4's owner: " << territory4->getTerritoryOwner()->get_name() << endl;
        
    }
}