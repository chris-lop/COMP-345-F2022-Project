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
    
    /*
    cout << "------- Testing Advance Order -------" <<"\n";
    Advance *advT1 = new Advance(t1, t2, p, 5);
    Advance *advT2 = new Advance(t2, t2, p, 5);
    cout << "# Verifying that advance order checks ownership of source territory #\n";
    cout << "Advance 1 valid (from territory1 to territory 2, Marc moves 5 units): " << advT1->validate() << "\n";
    cout << "Advance 2 valid (from territory2 to territory 1, Marc moves 5 units): " << advT2->validate() << "\n";
    "# Verifying that advance order checks the number of units in source territory #\n";
    */

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

   /*
    cout << "------- Testing Bomb Order -------" <<"\n";
    Bomb *bmbT1 = new Advance(t1, p);
    Bomb *bmbT2 = new Advance(t2, p);
    cout << "# Verifying that bomb order checks ownership of target territory #\n";
    cout << "Bomb 1 valid (Marc bombs t1): " << bmbT1->validate() << "\n";
    cout << "Bomb 2 valid (Marc bombs t2): " << bmbT2->validate() << "\n";
    */


   delete t1; delete t2; delete t3;
   delete a1; delete a2; delete a3;
   delete deployT1; delete deployT2; delete deployT1_units;
}