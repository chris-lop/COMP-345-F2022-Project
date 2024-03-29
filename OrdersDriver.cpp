#include <iostream> 
#include <algorithm>
#include "Orders.h"
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

using std::cout;
using std::endl;

void resetOwnership(Territory *territory1, Territory *territory2, Territory *territory3, Territory *territory4, Player *player1, Player *player2);

void testOrderExecution() {
    Territory *t1 = new Territory(new string("t1"), new string("cont1"), vector<Territory*>{}, nullptr, new int(5));
    Territory *t2 = new Territory(new string("t2"), new string("cont1"), vector<Territory*>{t1}, nullptr, new int(5));
    t1->setAdjTerritories(vector<Territory*> {t2});
    Player *p = new Player("Marc", {t1}, nullptr, {});
    Player *other = new Player("asd", {t2}, nullptr, {});
    p->set_armyUnit(8);
    other->set_armyUnit(8);
    t1->setTerritoryOwner(p);
    t2->setTerritoryOwner(other);
    
    cout << "########## TESTING ORDER EXECUTION ##########" <<"\n";
    cout << "Territory 1: " << *t1 << " Territory 2: " << *t2 << " Player: " << *p <<"\n";
    Deploy *deployT1 = new Deploy(t1, p, 1);
    Deploy *deployT2 = new Deploy(t2, p, 1);
    //cout << "deployT1: " << *deployT1 << " deployT2: " << *deployT2 << "\n";
    cout << "------- Testing Deploy Order -------" <<"\n";
    cout << "# Verifying that deploy order checks ownership #\n";
    cout << "Deploy 1 valid (for territory1, move 1 unit): " << deployT1->validate() << "\n";
    cout << "Deploy 2 valid (for territory2, move 1 unit): " << deployT2->validate() << "\n";

    cout << "# See the effect string #" << endl;
    deployT1->execute();
    cout << "Deploy 1 has executed, effect: " << deployT1->getEffect() << endl;

    cout << "# Verifying that deploy order checks the number of units in reinforcement pool #\n";
    Deploy *deployT1_units = new Deploy(t1, p, 10);
    cout << "Deploy 1 valid (for territory1, move 10 units): " << deployT1_units->validate() << "\n";
    
    
    cout << "------- Testing Advance Order -------" <<"\n";
    Territory *territory1 = new Territory(new string("territory1"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    Territory *territory2 = new Territory(new string("territory2"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    Territory *territory3 = new Territory(new string("territory3"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    Territory *territory4 = new Territory(new string("territory4"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    territory1->setAdjTerritories(vector<Territory*> {territory2});
    territory2->setAdjTerritories(vector<Territory*> {territory1, territory3, territory4});
    territory3->setAdjTerritories(vector<Territory*> {territory2});
    territory4->setAdjTerritories(vector<Territory*> {territory2});
    Player *player1 = new Player("Chris", {territory1, territory3}, nullptr, {});
    Player *player2 = new Player("Marc", {territory2, territory4}, nullptr, {});
    territory1->setTerritoryOwner(player1);
    territory2->setTerritoryOwner(player2);
    territory3->setTerritoryOwner(player1);
    territory4->setTerritoryOwner(player2);

    Advance *advT1 = new Advance(territory1, territory2, player1, 5);
    Advance *advT2 = new Advance(territory2, territory1, player1, 5);
    Advance *advT3 = new Advance(territory1, territory2, player1, 10);
    Advance *advT4 = new Advance(territory1, territory3, player1, 5);
    Advance *advT5 = new Advance(territory2, territory4, player2, 2);

    cout << "Current State of territories:" << endl;
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << " Territory 3: " << *territory3 << " Territory 4: " << *territory4 <<  "\n";
    cout << "# Verifying that advance order checks ownership of source territory #\n";
    cout << "Advance 1 (from territory1 to territory 2, Chris moves 5 units): " << advT1->validate() << "\n";
    cout << "Advance 2 (from territory2 to territory 1, Chris moves 5 units): " << advT2->validate() << "\n";
    cout << "# Verifying that advance order checks the number of units in source territory #\n";
    cout << "Advance 3 (from territory1 to territory 2, Chris moves 10 units): " << advT3->validate() << "\n";
    cout << "# Verifying that advance order checks adjacency of territories #\n";
    cout << "Advance 4 (from territory1 to territory 3, Chris moves 5 units): " << advT3->validate() << "\n";
    cout << "# Executing an advance order that results in a movement of units #\n";
    advT5->execute();
    //cout << "# Executing an advance order that results in an attack #\n";
    //advT1->execute();
    cout << "Current State of territories after execution of advance order (from t2->t4, 2 units):" << endl;
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << " Territory 3: " << *territory3 << " Territory 4: " << *territory4 <<  "\n";

    cout << "#### Checking that territory ownership changes when territory is conquered #####\n";
    territory2->setArmy(new int(1));
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << "\n";
    cout << "Executing advance 1 (from territory1 to territory 2, Chris moves 5 units)\n";
    advT1->execute();
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << "\n";



   cout << "------- Testing Airlift Order -------\n";
   Territory *t3 = new Territory(new string("t3"), new string("cont1"), vector<Territory*>{t2}, p, new int(5));
   vector<Territory*> playerTerritories = p->get_trt();
   playerTerritories.push_back(t3);
   p->set_Trt(playerTerritories);
   Airlift *a1 = new Airlift(t1, t2, p, 1);
   Airlift *a2 = new Airlift(t1, t3, p, 1);
   cout << "Territory 3: " << *t3 << endl /*<< "a1: " << *a1 << " a2: " << *a2 << endl*/;
   cout << "# Verifying that airlift validate checks the ownership of territories #" << endl;
   cout << "Airlift 1 valid (t1->t2 1 unit): " << a1->validate() << endl;
   cout << "Airlift 2 valid (t1->t3 1 unit): " << a2->validate() << endl;
   
   cout << "# See the effect string #" << endl;
   a2->execute();
   cout << "a2 has executed, effect:" << a2->getEffect() << endl;
   Airlift *a3 = new Airlift(t1, t3, p, 10);
   // cout << "a3: " << *a3 << endl;


   cout << "# Verifying that airlift validate checks number of armies #" << endl;
   cout << "Airlift 3 valid (t1->t3 10 units): " << a3->validate() << endl;

   
    cout << "------- Testing Bomb Order -------" <<"\n";
    Bomb *bmbT1 = new Bomb(territory1, player1);
    Bomb *bmbT2 = new Bomb(territory2, player1);
    Bomb *bmbT3 = new Bomb(territory1, player2);

    cout << "# Verifying that bomb order checks ownership of target territory #\n";
    cout << "Bomb 1 valid (Chris bombs territory1): " << bmbT1->validate() << "\n";
    cout << "Bomb 2 valid (Chris bombs territory2): " << bmbT2->validate() << "\n";

    cout << "# Verifying that bomb order checks adjacency of territories #\n";
    cout << "Bomb 3 (Marc bombs territory1): " << bmbT3->validate() << "\n";
    
    cout << "# Executing a valid bomb order #\n";
    bmbT2->execute();

    cout << "Current State of territories after execution of bomb order on Territory4:" << endl;
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << " Territory 3: " << *territory3 << " Territory 4: " << *territory4 <<  "\n";

    cout << "------- Testing Blockade Order -------" <<"\n";
    Blockade *blockade1 = new Blockade(territory3, player2);
    Blockade *blockade2 = new Blockade(territory3, player1);

    cout << "# Verifying that blockade order checks ownership of target territory #\n";
    cout << "Blockade 1 validation (Marc blockades territory3): " << blockade1->validate() << "\n";
    cout << "Blockade 2 validation (Chris blockades territory3): " << blockade2->validate() << "\n";
    
    cout << "# Executing a valid Blockade order #\n";
    blockade2->execute();

    cout << "Current State of territories after execution of Blockade order on Territory3:" << endl;
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << " Territory 3: " << *territory3 << " Territory 4: " << *territory4 <<  "\n";


   cout << "------- Testing negotiate order -------\n";
   cout << "#### Checking Negotiate with Advance ####\n";
   Advance *advance1 = new Advance(t1, t2, p, 1);
   cout << "Checking that advance order between territories owned by player 1 and player 2 is valid\n";
   cout << "advance1 valid (territory 1 and 2): " << advance1->validate() << endl;
   Negotiate *n1 = new Negotiate(p, other);
   n1->execute();
   cout << "# Checking that negotiation blocks an advance order #\n";
   cout << "Now, a negotiation has been created betweent the players: " << n1->getEffect() << "\n";
   cout << "advance1 valid: " << advance1->validate() << endl;
   cout << "# Checking that a new turn starting stops the negotiation #\n";
   p->set_armyUnit(p->get_armyUnit() + 3);
   other->set_armyUnit(other->get_armyUnit() + 3);
   cout << "advance1 valid: " << advance1->validate() << endl;

   cout << "#### Checking Negotiate with Bomb ####\n";
   Bomb *bomb1 = new Bomb(t2, p);
   cout << "Seeing that created bomb order is valid\n";
   cout << "bomb1 validate (t2): " << bomb1->validate() << endl;
   cout << "# Checking that Negotiate blocks a Bomb order #\n";
   delete n1;
   n1 = new Negotiate(p, other);
   n1->execute();
   cout << "Negotiation: " << n1->getEffect() << "\n";
   cout << " bomb1 valid: " << bomb1->validate() << endl;
   cout << "# Checking that a new turn starting stops the negotiation #\n";
   p->set_armyUnit(p->get_armyUnit() + 3);
   other->set_armyUnit(other->get_armyUnit() + 3);
   cout << "bomb1 valid: " << bomb1->validate() << endl;
   
   cout << "#### Checking Negotiate valid() method ####\n";
   Negotiate *n2 = new Negotiate(p, p);
   Negotiate *n3 = new Negotiate(p, other);
   cout << "Seeing that a negotiate order from a player to themselves is invalid\n";
   cout << "n2 valid (between p1 and p1): " << n2->validate() << endl;
   cout << "Seeing that a negotiate order b/w two different players is valid\n";
   cout << "n3 valid (between p1 and p2): " << n3->validate() << endl;
   
   


   delete t1; delete t2; delete t3;
   delete a1; delete a2; delete a3;
   delete n1; delete advance1; delete bomb1;
   delete n2; delete n3;
   delete deployT1; delete deployT2; delete deployT1_units;

   delete player1; delete player2;
   delete advT1; delete advT2; delete advT3; delete advT4; delete advT5;
   delete bmbT1; delete bmbT2; delete bmbT3;
   delete blockade1; delete blockade2;


    cout << "\n########## TESTING ORDERS WITH GAME ENGINE ##########" <<"\n";
    /*
        This is re-setting up the territories from above
    */
    territory1 = new Territory(new string("territory1"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    territory2 = new Territory(new string("territory2"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    territory3 = new Territory(new string("territory3"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    territory4 = new Territory(new string("territory4"), new string("continent1"), vector<Territory*>{}, nullptr, new int(5));
    territory1->setAdjTerritories(vector<Territory*> {territory2});
    territory2->setAdjTerritories(vector<Territory*> {territory1, territory3, territory4});
    territory3->setAdjTerritories(vector<Territory*> {territory2});
    territory4->setAdjTerritories(vector<Territory*> {territory2});
    Hand *hand1 = new Hand();
    Hand *hand2 = new Hand();
    OrdersList *o1 = new OrdersList(), *o2 = new OrdersList();
    player1 = new Player("Chris", {territory1, territory3}, hand1, o1);
    player2 = new Player("Marc", {territory2, territory4}, hand2, o2);
    player1->set_armyUnit(1); player2->set_armyUnit(1);
    resetOwnership(territory1, territory2, territory3, territory4, player1, player2);
    
    Map *map = new Map();
    map->territories = vector<Territory*> {territory1, territory2, territory3, territory4};
    GameEngine *engine = new GameEngine(map, vector<Player*> {player1, player2});
    engine->setDeck(new Deck());
    cout << "------ Testing Deploy and Advance ------\n";
    engine->issueOrdersPhase(vector<Player*>{player1, player2});
    engine->executeOrdersPhase();

    cout << "------ Testing Airlift, Bomb, Negotiate ------\n";
    for (int i = 0; i < 3; i++) {
        hand1->addCard(new Card("Airlift")); hand2->addCard(new Card("Airlift"));
        hand1->addCard(new Card("Bomb")); hand2->addCard(new Card("Bomb"));
        hand1->addCard(new Card("Diplomacy")); hand2->addCard(new Card("Diplomacy"));
    }
    for (int i = 0; i < 4; i++) {
        engine->issueOrdersPhase(vector<Player*>{player1, player2});
        engine->executeOrdersPhase();
        resetOwnership(territory1, territory2, territory3, territory4, player1, player2);
    }

    delete player1; delete player2;
}

void resetOwnership(Territory *territory1, Territory *territory2, Territory *territory3, Territory *territory4, Player *player1, Player *player2) {
    territory1->setTerritoryOwner(player1);
    territory2->setTerritoryOwner(player2);
    territory3->setTerritoryOwner(player1);
    territory4->setTerritoryOwner(player2);
    player1->set_Trt(vector<Territory*> {territory1, territory3});
    player2->set_Trt(vector<Territory*> {territory2, territory4});
}
