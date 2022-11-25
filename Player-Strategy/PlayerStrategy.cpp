#include "PlayerStrategy.h"
#include "../Player.h"

PlayerStrategy::PlayerStrategy(Player* p): p(p){}

PlayerStrategy::~PlayerStrategy() {
    // Freeing the Player* is the job of the player
}


//-----------------------------------//
//  AGGRESSIVE PLAYER IMPLEMENTATION //
//-----------------------------------//

// Constructors / Destructors
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p): PlayerStrategy(p) {}
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

// issueOrder (How does an aggressive player decide which order to issue)
void AggressivePlayerStrategy::issueOrder()
{
    
}

// toAttack (How does an aggressive player decide which territories to attack)
std::vector <Territory*> AggressivePlayerStrategy::toAttack()
{
    vector <Territory*> result_attack;
    vector<Territory*> trt = this->p->get_trt();

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

// toDefend (How does an aggressive player decide which territories to defend)
std::vector <Territory*> AggressivePlayerStrategy::toDefend()
{
    return vector<Territory*>{};
}

//-----------------------------------//
//  NEUTRAL PLAYER IMPLEMENTATION    //
//-----------------------------------//

// Constructors / Destructors
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p): PlayerStrategy(p) {}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

// issueOrder (How does a neutral player decide which order to issue)
void NeutralPlayerStrategy::issueOrder()
{
    
}

// toAttack (How does a neutral player decide which territories to attack)
// Neutral players never issue any orders or issue any cards, therefore they never will never attack
std::vector <Territory*> NeutralPlayerStrategy::toAttack()
{
    return vector<Territory*>{};
}

// toDefend (How does a neutral player decide which territories to defend)
// Neutral players never issue any orders or issue any cards, therefore they never will never defend
std::vector <Territory*> NeutralPlayerStrategy::toDefend()
{
    return vector<Territory*>{};
}

