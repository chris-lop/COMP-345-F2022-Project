#pragma once
#include "PlayerStrategy.h"
#include "../Player.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "../Cards.h"
using namespace std;

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
    // trt declaration
    vector<Territory*> trt = this->p->get_trt();
    //vector territory to be returned as result
    std::vector <Territory*> result_attack;
 
    for (Territory* t : trt){
        //traverse the list of adjacent territories for each territory t
        for(Territory* t_adj: t->getAdjTerritories()){
            for (Territory * a_territory : trt)
            {
                
            }

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

// toDefend (list of territories to defend)
std::vector <Territory*> AggressivePlayerStrategy::toDefend()
{
    // trt declaration
    vector<Territory*> trt = this->p->get_trt();
    
    //new vector of Territory to be returned as result
    std::vector <Territory*> result_defend; 

    for (Territory* t : trt){
        
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
    // issueOrder Starting Message
    cout << "Issued Orders:" << endl;

    // Variable to keep track of reinforcement
    int deployed_units = 0;

    for (Order* o : this->p->get_olst()->getOrder())
    {
        // If this order is of type Deploy
        if (o->getType() == "Deploy" || o->getType() == "deploy")
        {
            // Increment deployed_units
            Deploy *d = (Deploy *) o;
            deployed_units = deployed_units+d->getNumberUnits();
        }
    }

    // Vector to keep track of issued orders
    vector <string> issued_orders;

    while (true)
    {
        // If reinforcement pool of player isn't empty, player can only use Deploy orders
        if (this->p->get_armyUnit()-deployed_units != 0)
        {            
            // Saving player's territories
            vector <Territory*> trt_defend = this->p->get_trt();

            // Find strongest territory from player's territories
            int trt_defend_ctr = 0;
            int highestArmyIndex = 0;
            int highestArmy = -1;

            for(Territory* t: trt_defend)
            {
                if (*t->getArmy()>highestArmy)
                {
                    highestArmy = *t->getArmy();
                    highestArmyIndex = trt_defend_ctr;
                }

                trt_defend_ctr++;
            }

            // Ask for which territory player wants to deploy units to
            int trt_defend_choice = highestArmyIndex+1;

            // Increment deployed_units by this value
            deployed_units = deployed_units + this->p->get_armyUnit();

            // Create Deploy order with data above
            Deploy* d = new Deploy(trt_defend[trt_defend_choice-1], this->p, this->p->get_armyUnit());

            // Add deploy order to player's order list
            this->p->get_olst()->addOrder(d); 

            // Add to issed orders vector for display later
            issued_orders.push_back("Deploy | To: "+*trt_defend[trt_defend_choice-1]->getTerritoryName()+" | "+to_string(this->p->get_armyUnit())+" units");
            
        }
        // Else, the reinforcement pool is empty, let player give other orders
        else
        {
            // Boolean variable to check if player possesses cards
            bool hasAirlift = false;
            bool hasBomb = false;
            bool hasBlockade = false;
            bool hasdiplomacy = false;
            
            // Check through a player's hand and check if he has order cards, count them
            int airlift_ctr = 0;
            int bomb_ctr = 0;
            
            for (Card* c : this->p->get_Phand()->cardList())
            {
                // If player has airlift card, save it in boolean variable
                if (c->getType() == "Airlift" || c->getType() == "airlift")
                {
                    hasAirlift = true;
                    airlift_ctr++;
                    continue;
                }
                // If player has bomb card, save it in boolean variable 
                if (c->getType() == "Bomb" || c->getType() == "bomb")
                {
                    hasBomb = true;
                    bomb_ctr++;
                    continue;
                }

                // Ignore blockade and diplomacy because aggressive players do not use these cards
            }

            // Check through a player's issued orders and count usage of other cards
            for (Order* o : this->p->get_olst()->getOrder())
            {
                // If this order is of type Airlift
                if (o->getType() == "Airlift" || o->getType() == "airlift")
                {
                    airlift_ctr--;
                    continue;
                }
                // If this order is of type Bomb
                if (o->getType() == "Bomb" || o->getType() == "bomb")
                {
                    bomb_ctr--;
                    continue;
                }
            }

            // If ctrs = 0, disable this option
            if (airlift_ctr == 0)
            {
                hasAirlift = false;
            }

            if (bomb_ctr == 0)
            {
                hasBomb = false;
            }

            // Group units
            bool unitsGrouped = false;

            // Check if units are grouped
            int territories_with_units = 0;

            for (Territory* t : this->p->get_trt())
            {
                if (*t->getArmy() > 0)
                {
                    territories_with_units++;
                }
            }

            if (territories_with_units == 1)
            {
                unitsGrouped = true;
            }

            // if units are not grouped, group them using advance or airlift
            if (!unitsGrouped)
            {
                // If has airlift, use it to move units from farthest territory to strongest territory
                if (hasAirlift)
                {

                    // Saving player's territories
                    vector <Territory*> trt_defend = this->p->get_trt();

                    // Find strongest territory from player's territories
                    int trt_defend_ctr = 0;
                    int highestArmyIndex = 0;
                    int highestArmy = -1;

                    for(Territory* t: trt_defend)
                    {
                        if (*t->getArmy()>highestArmy)
                        {
                            highestArmy = *t->getArmy();
                            highestArmyIndex = trt_defend_ctr;
                        }

                        trt_defend_ctr++;
                    }

                    // Find farthest friendly territory from strongest territory

                    //--------------------------------------------------//
                    //  FINAL BFS TO FIND FARTHEST NODE WITH UNITS      //
                    //--------------------------------------------------//

                    // mark all distance with -1
                    vector<int> visited;
                    visited.resize(trt_defend.size(), -1);

                    // Create a queue for BFS and a counter to track the amount of visited territories
                    list<Territory> queue;

                    // Set starting starting node distance to 0 and enqueue it into queue
                    visited[highestArmyIndex] = 0;
                    queue.push_back(*trt_defend[highestArmyIndex]);

                    // Start of BFS
                    while (!queue.empty())
                    {
                        // Dequeue territory from queue
                        Territory t = queue.front();
                        queue.pop_front();

                        // True index of t
                        int true_index_t = -1;
                        for (int i = 0; i < trt_defend.size() ; i++)
                        {   
                            if (trt_defend[i]->getTerritoryName() == t.getTerritoryName())
                            {
                                true_index_t = i;
                            }
                        }

                        // Get all adjacent territories of the dequeued territory t. If a adjacent has not been visited, then mark it visited and enqueue it
                        for (auto adjacent : t.AdjTerritories)
                        {
                            Territory aTerritory = *adjacent;

                            // True Index of aTerritory in trt_defend
                            int true_index = -1;
                            for (int i = 0; i < trt_defend.size() ; i++)
                            {   
                                if (trt_defend[i]->getTerritoryName() == aTerritory.getTerritoryName())
                                {
                                    true_index = i;
                                }
                            }

                            // make this distance one more than previous distance
                            if (visited[true_index] == -1)
                            {
                                visited[true_index] = visited[true_index_t]+1;
                                queue.push_back(aTerritory);
                            }
                        }
                    }

                    // Iterate through visited vector and find farthest node that has army units
                    int maxDistance = -1;
                    int territory_index;

                    for (int i = 0; i < visited.size(); i++)
                    {
                        if (visited[i] > maxDistance && *trt_defend[i]->getArmy()!=0)
                        {
                            maxDistance = visited[i];
                            territory_index = i;
                        }
                    }

                    // Create airlift order on this node to move its units to strongest territory
                    Airlift* a = new Airlift(trt_defend[territory_index], trt_defend[highestArmyIndex], this->p , *trt_defend[territory_index]->getArmy());

                    // Add Airlift order to player's order list
                    this->p->get_olst()->addOrder(a);

                    // Add to issed orders vector for display later
                    issued_orders.push_back("Airlift | From: "+*trt_defend[territory_index]->getTerritoryName()+" | To: "+*trt_defend[highestArmyIndex]->getTerritoryName()+" | "+to_string(*trt_defend[territory_index]->getArmy())+" units");
                }
                // Else, move units to strongest territory using advance
                else
                {

                    // Saving player's territories
                    vector <Territory*> trt_defend = this->p->get_trt();

                    // Find strongest territory from player's territories
                    int trt_defend_ctr = 0;
                    int highestArmyIndex = 0;
                    int highestArmy = -1;

                    for(Territory* t: trt_defend)
                    {
                        if (*t->getArmy()>highestArmy)
                        {
                            highestArmy = *t->getArmy();
                            highestArmyIndex = trt_defend_ctr;
                        }

                        trt_defend_ctr++;
                    }

                    // Find farthest friendly territory from strongest territory

                    //--------------------------------------------------//
                    //  FINAL BFS TO FIND FARTHEST NODE WITH UNITS      //
                    //--------------------------------------------------//

                    // mark all distance with -1
                    vector<int> visited;
                    visited.resize(trt_defend.size(), -1);

                    // Create a queue for BFS and a counter to track the amount of visited territories
                    list<Territory> queue;

                    // Set starting starting node distance to 0 and enqueue it into queue
                    visited[highestArmyIndex] = 0;
                    queue.push_back(*trt_defend[highestArmyIndex]);

                    // Start of BFS
                    while (!queue.empty())
                    {
                        // Dequeue territory from queue
                        Territory t = queue.front();
                        queue.pop_front();

                        // True index of t
                        int true_index_t = -1;
                        for (int i = 0; i < trt_defend.size() ; i++)
                        {   
                            if (trt_defend[i]->getTerritoryName() == t.getTerritoryName())
                            {
                                true_index_t = i;
                            }
                        }

                        // Get all adjacent territories of the dequeued territory t. If a adjacent has not been visited, then mark it visited and enqueue it
                        for (auto adjacent : t.AdjTerritories)
                        {
                            Territory aTerritory = *adjacent;

                            // True Index of aTerritory in trt_defend
                            int true_index = -1;
                            for (int i = 0; i < trt_defend.size() ; i++)
                            {   
                                if (trt_defend[i]->getTerritoryName() == aTerritory.getTerritoryName())
                                {
                                    true_index = i;
                                }
                            }

                            // make this distance one more than previous distance
                            if (visited[true_index] == -1)
                            {
                                visited[true_index] = visited[true_index_t]+1;
                                queue.push_back(aTerritory);
                            }
                        }
                    }

                    // Iterate through visited vector and find farthest node that has army units
                    int maxDistance = -1;
                    int territory_index;

                    for (int i = 0; i < visited.size(); i++)
                    {
                        if (visited[i] > maxDistance && *trt_defend[i]->getArmy()!=0)
                        {
                            maxDistance = visited[i];
                            territory_index = i;
                        }
                    }

                    // Search through this territory's adjacent territories
                    for (int i = 0; i < trt_defend[territory_index]->getAdjTerritories().size(); i++)
                    {
                        // Save adjacent territories vector
                        vector<Territory*> adjacent_territories = trt_defend[territory_index]->getAdjTerritories();

                        // Var for true index
                        int true_index = 0;

                        // search through original vector and increment true_index until index of this territory is found in original vector
                        for (Territory* t : trt_defend)
                        {
                            if (t == adjacent_territories[0])
                            {
                                break;
                            }
                            else
                            {
                                true_index++;
                            }
                        }  

                        // If this adjacent territory is closer to the strongest territory, move all of your units there with advance
                        if (visited[true_index] < visited[territory_index])
                        {

                            // Create Advance order
                            Advance* a = new Advance(trt_defend[territory_index], trt_defend[true_index], this->p , *trt_defend[territory_index]->getArmy());

                            // Add deploy order to player's order list
                            this->p->get_olst()->addOrder(a);

                            // Add to issed orders vector for display later
                            issued_orders.push_back("Advance (Troop Movement) | From: "+*trt_defend[territory_index]->getTerritoryName()+" | To: "+*trt_defend[true_index]->getTerritoryName()+" | "+to_string(*trt_defend[territory_index]->getArmy())+" units");
                            break;
                        }
                    }
                }
            }
            // If units are grouped, attack enemy unsing advance or bomb
            else
            {

                // Territory ptr to point to territory with army and adjacent enemy territory
                Territory *enemy_adj_territory = NULL;
                Territory *army_territory = NULL;

                // find territory with army
                for (Territory* t : this->p->get_trt())
                {
                    if (*t->getArmy() > 0)
                    {
                        army_territory = t;
                        break;
                    }
                }

                // Check if units are adjacent to enemy territory
                bool adjacent_enemy = false;

                for (Territory* t : army_territory->getAdjTerritories())
                {
                    if (t->getTerritoryOwner() != this->p)
                    {
                        adjacent_enemy = true;
                        enemy_adj_territory = t;
                        break;
                    }
                }

                // If units are adjacent to enemy territory
                if (adjacent_enemy)
                {
                    // If has bomb, use it on adjacent enemy territory
                    if (hasBomb)
                    {

                        // Create Bomb order with data above
                        Bomb* b = new Bomb(enemy_adj_territory, this->p);

                        // Add Bomb order to player's order list
                        this->p->get_olst()->addOrder(b);

                        // Add to issued orders vector for display later
                        issued_orders.push_back("Bomb | Target: "+*enemy_adj_territory->getTerritoryName());
                    }
                    // Else, attack adjacent enemy territory
                    else
                    {

                        // Create Advance order with data above
                        Advance* a = new Advance(army_territory, enemy_adj_territory, this->p , *army_territory->getArmy());

                        // Add deploy order to player's order list
                        this->p->get_olst()->addOrder(a);

                        // Add to issed orders vector for display later
                        issued_orders.push_back("Advance (Attack) | From: "+*army_territory->getTerritoryName()+" | To: "+*enemy_adj_territory->getTerritoryName()+" | "+to_string(*army_territory->getArmy())+" units");
                    }
                }
            }
        }

        // Print issued orders    
        for (string s : issued_orders)
        {
            cout << s << endl;
        }
        
        cout << endl;
        break;
    }
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

