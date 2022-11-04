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
    p->set_armyUnit(8);
    t1->setTerritoryOwner(p);
    t2->setTerritoryOwner(p);
    
    cout << "Verifying that deploy order checks ownership\n";
    Deploy *deployT1 = new Deploy(t1, p, 5);
    Deploy *deployT2 = new Deploy(t2, p, 5);
    cout << "Deploy 1 valid (should be true): " << deployT1->validate() << "\n";
    cout << "Deploy 2 valid (should be false): " << deployT2->validate() << "\n";
    
}