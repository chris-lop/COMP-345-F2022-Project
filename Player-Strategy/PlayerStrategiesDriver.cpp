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
        cout << "\nPlayer 1 has conquered all the territories and won the game!";
    }
}