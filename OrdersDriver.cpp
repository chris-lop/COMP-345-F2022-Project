#include <iostream> 
#include "Orders.h"
#include <algorithm>

using std::cout;
using std::endl;

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
    cout << "# Executing an advance order that results in an attack #\n";
    advT1->execute();
    cout << "Current State of territories after execution of advance orders:" << endl;
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << " Territory 3: " << *territory3 << " Territory 4: " << *territory4 <<  "\n";

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
    Bomb *bmbT2 = new Bomb(territory4, player1);
    Bomb *bmbT3 = new Bomb(territory1, player2);

    cout << "# Verifying that bomb order checks ownership of target territory #\n";
    cout << "Bomb 1 valid (Chris bombs territory1): " << bmbT1->validate() << "\n";
    cout << "Bomb 2 valid (Chris bombs territory4): " << bmbT2->validate() << "\n";

    cout << "# Verifying that bomb order checks adjacency of territories #\n";
    cout << "Bomb 3 (Marc bombs territory1): " << bmbT3->validate() << "\n";
    
    cout << "# Executing a valid bomb order #\n";
    bmbT2->execute();

    cout << "Current State of territories after execution of bomb order on Territory4:" << endl;
    cout << "Territory 1: " << *territory1 << " Territory 2: " << *territory2 << " Territory 3: " << *territory3 << " Territory 4: " << *territory4 <<  "\n";


   cout << "------- Testing negotiate order -------\n";
   cout << "#### Checking Negotiate with Advance ####\n";
   Advance *advance1 = new Advance(t1, t2, p, 1);
   cout << "Checking that advance order between territories owned by player 1 and player 2 is valid\n";
   cout << "advance1->validate(): " << advance1->validate() << endl;
   Negotiate *n1 = new Negotiate(p, other);
   n1->execute();
   cout << "# Checking that negotiation blocks an advance order #\n";
   cout << "Now, a negotiation has been created betweent the players\n";
   cout << "advance1->validate(): " << advance1->validate() << endl;
   cout << "# Checking that a new turn starting stops the negotiation #\n";
   p->set_armyUnit(p->get_armyUnit() + 3);
   other->set_armyUnit(other->get_armyUnit() + 3);
   cout << "advance1->validate(): " << advance1->validate() << endl;

   cout << "#### Checking Negotiate with Bomb ####\n";
   Bomb *bomb1 = new Bomb(t2, p);
   cout << "Seeing that created bomb order is valid\n";
   cout << "bomb1->validate(): " << bomb1->validate() << endl;
   cout << "# Checking that Negotiate blocks a Bomb order #\n";
   n1->execute();
   cout << "bomb1->validate(): " << bomb1->validate() << endl;
   cout << "# Checking that a new turn starting stops the negotiation #\n";
   p->set_armyUnit(p->get_armyUnit() + 3);
   other->set_armyUnit(other->get_armyUnit() + 3);
   cout << "bomb1->validate(): " << bomb1->validate() << endl;
   
   cout << "#### Checking Negotiate valid() method ####\n";
   Negotiate *n2 = new Negotiate(p, p);
   Negotiate *n3 = new Negotiate(p, other);
   cout << "Seeing that a negotiate order from a player to themselves is invalid\n";
   cout << "n2->validate(): " << n2->validate() << endl;
   cout << "Seeing that a negotiate order b/w two different players is valid\n";
   cout << "n3->validate(): " << n3->validate() << endl;
   
   


   delete t1; delete t2; delete t3;
   delete a1; delete a2; delete a3;
   delete n1; delete advance1; delete bomb1;
   delete n2; delete n3;
   delete deployT1; delete deployT2; delete deployT1_units;
}