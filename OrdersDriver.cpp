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
    
    cout << "Territory 1: " << *t1 << " Territory 2: " << *t2 << " Player: " << *p <<"\n";
    Deploy *deployT1 = new Deploy(t1, p, 5);
    Deploy *deployT2 = new Deploy(t2, p, 5);
    //cout << "deployT1: " << *deployT1 << " deployT2: " << *deployT2 << "\n";
    cout << "# Verifying that deploy order checks ownership #\n";
    cout << "Deploy 1 valid (for territory1, move 5 units): " << deployT1->validate() << "\n";
    cout << "Deploy 2 valid (for territory2, move 5 units): " << deployT2->validate() << "\n";
    cout << "# Verifying that deploy order checks the number of units in reinforcement pool #\n";
    Deploy *deployT1_units = new Deploy(t1, p, 10);
    cout << "Deploy 1 valid (for territory1, move 10 units): " << deployT1_units->validate() << "\n";
}