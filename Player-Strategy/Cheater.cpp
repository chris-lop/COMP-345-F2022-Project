#include "Cheater.h"
#include "../Player.h"
#include <vector>
using std::vector;
#include <algorithm>
using std::find;
#include <iostream>
using std::cout; using std::endl;

Cheater::Cheater(Player* p): PlayerStrategy(p) {}
Cheater::~Cheater() {}

void Cheater::issueOrder() {
    // The cheater straight up conquers adjacent territories
    vector <Territory*> result_attack = toAttack();
    for (Territory* t: result_attack) {
        cout << "Taking territory " << *t << endl;
        Player *oldOwner = t->getTerritoryOwner();
        // Make ourselves owner
        t->setTerritoryOwner(p);

        vector<Territory*> ownedTerritories = p->get_trt();
        ownedTerritories.push_back(t);
        p->set_Trt(ownedTerritories);
        
        // Remove ownership from other player
        vector<Territory*> oldOwnerTerritories = oldOwner->get_trt();
        cout << "OLD TERRITORIES\n";
        for (auto t: oldOwnerTerritories) {
            cout << *(t->getTerritoryName()) << " ";
        }
        cout << endl;

        for (auto it = oldOwnerTerritories.begin(); it < oldOwnerTerritories.end(); ++it) {
            if (*it == t) {
                oldOwnerTerritories.erase(it);
                break;
            }
        }

        cout << "NEW TERRITORIES\n";
        for (auto t: oldOwnerTerritories) {
            cout << *(t->getTerritoryName()) << " ";
        }
        cout << endl;
        
        oldOwner->set_Trt(oldOwnerTerritories);
    }
}


std::vector <Territory*> Cheater::toAttack() {
    vector <Territory*> result_attack;
    vector<Territory*> trt = p->get_trt();

    for (Territory* t : trt){
        //traverse the list of adjacent territories for each territory t
        for(Territory* t_adj: t->getAdjTerritories()){

            if ((find(trt.begin(), trt.end(), t_adj)) != trt.end()){
                //The adjacent territory was found in the list of owned territories
                //We don't need to attack the territory t
                continue;
            }

            //The adjacent territory was not found in owned territories, thus, the territory t_adj can be attacked
            else{
                //if the territory to attack was already added, skip
                if((find(result_attack.begin(),result_attack.end(), t_adj)) != result_attack.end()){
                    continue;
                }
                //if not, add to the result vector
                else{result_attack.push_back(t_adj);}
            }

        }
    }

    return result_attack;
}

// The cheater never defends, so this is not needed
std::vector <Territory*> Cheater::toDefend() {
    return vector<Territory*>{};
}