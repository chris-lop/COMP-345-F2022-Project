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

// toAttack (list of territories to attack)
std::vector <Territory*> AggressivePlayerStrategy::toAttack()
{
    //vector territory to be returned as result
    std::vector <Territory*> result_attack;
 
    for (Territory* t : this->trt){
        //traverse the list of adjacent territories for each territory t
        for(Territory* t_adj: t->getAdjTerritories()){

            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end()){
                //The adjacent territory was found in the list of owned territories
                //We don't need to attack the territory t
                continue;
            }

            //The adjacent territory was not found in owned territories, thus, the territory t_adj can be attacked
            else{
                //if the territory to attack was already added, skip
                if((std::find(result_attack.begin(),result_attack.end(), t_adj)) != result_attack.end()){
                    continue;
                }
                //if not, add to the result vector
                else{result_attack.push_back(t_adj);}
            }

        }
    }

    return result_attack;
}

// toDefend (list of territories to defend)
std::vector <Territory*> AggressivePlayerStrategy::toDefend()
{
    //new vector of Territory to be returned as result
    std::vector <Territory*> result_defend; 

    for (Territory* t : this->trt){
        
        //traverse the list of adjacent territories for each t 
        for(Territory* t_adj: t->getAdjTerritories()){
            //verify if each territory in the adjacent territories list is in the list of territories owned
            
            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end()){
                //The adjacent territory was found in the list of owned territories
                //We don't need to defend the territory t
                continue;
            }

            //The adjacent territory was not found, thus, the territory t must be defended
            else{
                //if the territory to defend was already added, skip
                if((std::find(result_defend.begin(),result_defend.end(), t)) != result_defend.end()){
                    continue;
                }
                //if not, add to the result vector
                else{result_defend.push_back(t);}
            }
        }
    }
    return result_defend; 
}

// issueOrder (How does an aggressive player decide which order to issue)
void AggressivePlayerStrategy::issueOrder()
{
    
}

//-----------------------------------//
//  NEUTRAL PLAYER IMPLEMENTATION    //
//-----------------------------------//

// Constructors / Destructors
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p): PlayerStrategy(p) {}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

// issueOrder (How does a neutral player decide which order to issue)
// Neutral players never issue any orders or issue any cards, therefore they never will issueOrder()
void NeutralPlayerStrategy::issueOrder() { }

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

