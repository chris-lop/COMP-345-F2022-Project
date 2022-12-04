
#include "PlayerStrategy.h"
#include "Player.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "Cards.h"
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
bool AggressivePlayerStrategy::issueOrder()
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
                    int territory_index = -1;

                    for (int i = 0; i < visited.size(); i++)
                    {
                        if (visited[i] > maxDistance && *trt_defend[i]->getArmy()!=0)
                        {
                            maxDistance = visited[i];
                            territory_index = i;
                        }
                    }

                    // If no node has army units, do not issue airlift
                    if (territory_index != -1) {
                        // Create airlift order on this node to move its units to strongest territory
                        Airlift* a = new Airlift(trt_defend[territory_index], trt_defend[highestArmyIndex], this->p , *trt_defend[territory_index]->getArmy());

                        // Add Airlift order to player's order list
                        this->p->get_olst()->addOrder(a);

                        // Add to issed orders vector for display later
                        issued_orders.push_back("Airlift | From: "+*trt_defend[territory_index]->getTerritoryName()+" | To: "+*trt_defend[highestArmyIndex]->getTerritoryName()+" | "+to_string(*trt_defend[territory_index]->getArmy())+" units");
                    }

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
                    int territory_index = -1;

                    for (int i = 0; i < visited.size(); i++)
                    {
                        if (visited[i] > maxDistance && *trt_defend[i]->getArmy()!=0)
                        {
                            maxDistance = visited[i];
                            territory_index = i;
                        }
                    }
                    // If no territories have any army units, bail out
                    if (territory_index == -1) {
                        break;
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
    return (rand() % 100) < 60;
}

//-----------------------------------//
//  NEUTRAL PLAYER IMPLEMENTATION    //
//-----------------------------------//

// Constructors / Destructors
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p): PlayerStrategy(p) {}
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

// issueOrder (How does a neutral player decide which order to issue)
// Neutral players never issue any orders or issue any cards, therefore they never will issueOrder()
bool NeutralPlayerStrategy::issueOrder() {
    return false;
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


//-----------------------------------//
//  HUMAN PLAYER IMPLEMENTATION    //
//-----------------------------------//

// Constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* p): PlayerStrategy(p) {}

//Destructor
HumanPlayerStrategy::~HumanPlayerStrategy() {}


// toAttack 
// All adjacent territories not belonging to the human player can be attacked
std::vector <Territory*> HumanPlayerStrategy::toAttack()
{
    vector<Territory*> trt = this->p->get_trt();

    //vector territory to be returned as result
    std::vector <Territory*> result_attack;
 
    for (Territory* t : trt){
        //traverse the list of adjacent territories for each territory t
        for(Territory* t_adj: t->getAdjTerritories()){
            
            //The adjacent territory was found in the list of owned territories
            //We don't need to attack the territory t_adj
            if ((find(trt.begin(), trt.end(), t_adj)) != trt.end()){
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

// toDefend 
// All territories with adjacent enemy territories must be defended
std::vector <Territory*> HumanPlayerStrategy::toDefend()
{
    vector<Territory*> trt = this->p->get_trt();
    
    //new vector of Territory to be returned as result
    std::vector <Territory*> result_defend; 

    for (Territory* t : trt){
        
        //traverse the list of adjacent territories for each t 
        for(Territory* t_adj: t->getAdjTerritories()){
            //verify if each territory in the adjacent territories list is in the list of territories owned
            
            //The adjacent territory was found in the list of owned territories
            //We don't need to defend the territory t           
            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end()){
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


// issueOrder 
// For each order, ask user input
bool HumanPlayerStrategy::issueOrder() { 

    //Bool variables to determine player's cards
    bool hasAirlift = false;
    bool hasBomb= false;
    bool hasBlockade= false;
    bool hasDiplomacy= false;

    // Check through a player's hand and check if he has order cards
    for (Card* c : this->p->get_Phand()->cardList())
    {
        // If player has airlift card, save it in boolean variable
        if (c->getType() == "Airlift" || c->getType() == "airlift")
        {
            hasAirlift = true;
        }
        // If player has bomb card, save it in boolean variable 
        if (c->getType() == "Bomb" || c->getType() == "bomb")
        {
            hasBomb = true;
        }
        // If player has blockade card, save it in boolean variable
        if (c->getType() == "Blockade" || c->getType() == "blockade")
        {
            hasBlockade = true;
        }
        // If player has diplomacy card, save it in boolean variable 
        if (c->getType() == "Diplomacy" || c->getType() == "diplomacy")
        {
            hasDiplomacy = true;
        }
    }

    // Variable to keep track of the user input
    int orderNumber;
    bool done = false;
    // Vector to keep track of issued orders
    vector <string> issued_orders;

    while(!done){
        // issueOrder Starting Message
        cout<<"Please enter the order type (enter the number): \n";
        cout<<"1) Deploy\n2) Advance\n3) Bomb\n4) Blockade\n5) Airlift\n6) Negotiate\n";
        cin>>orderNumber;
        int option, army, t_option;
        bool input = true;
        bool input1 = true;
        bool input2 = true;
        
        // keep track of units deployed previously
        int deployed_unit = 0;

        for (Order* o : this->p->get_olst()->getOrder())
        {
            // If this order is of type Deploy
            if (o->getType() == "Deploy" || o->getType() == "deploy")
            {
                // Increment deployed_units var
                Deploy *d = (Deploy *) o;
                
                int new_num = d->getNumberUnits();
                deployed_unit = deployed_unit + new_num;
            }
        }

        switch(orderNumber){    
            //Deploy order case
            case 1:
                // Variable to keep track of the user input
                if(deployed_unit == this->p->get_armyUnit()){
                    cout<<"No more army units left in the pool, please select another order type.\n";
                    done = false;
                }
                else{
                    cout<<"Issuing Deploy Order\n";
                    cout<<"Please enter the territory you wish to deploy army units \n(select the number from your list of owned territories): \n";
                    vector <Territory*> defend = this->p->toDefend();
                    for(int i = 1; i<=p->get_trt().size();i++){
                        cout<<i<<") "<<*p->get_trt().at(i-1)->getTerritoryName()<<" ";
                    }
                    
                    // validate user input for territory selection
                    while(input1){
                        cout<<"\nEnter your selection: ";
                        cin>>option;
                        if(option<=p->get_trt().size()){
                            input1=false;
                        }
                        else{
                            cout<<"Please select the correct option from the list";
                        }
                    }
                    cout<<"How many army units to deploy to "<<*p->get_trt().at(option-1)->getTerritoryName()<<"?";
                    //validate user input for army units to deploy
                    
                    while(input2){
                        cout<<"\nEnter your selection: ";
                        cin>>army;
                        if(army <= this->p->get_armyUnit()-deployed_unit){
                            input2=false;
                        }
                        else{
                            cout<<"Please select the correct number\n";
                            cout<<"Current army units in the pool: "<<this->p->get_armyUnit()-deployed_unit;
                        }
                    }

                    Deploy* d = new Deploy(p->get_trt().at(option-1), this->p, army);
                    Territory* t = p->get_trt().at(option-1);
                    this->p->get_olst()->addOrder(d);
                    issued_orders.push_back("Deploy | To: " + *t->getTerritoryName() + " | " + to_string(army) + " units");
                    done = true;
                }
                break;//end of case Deploy
            
            //case of Advance order
            case 2:
                //verifying if all army units have been deployed
                if(deployed_unit < this->p->get_armyUnit()){
                    cout<<"Need to deploy all army units in the pool before issueing other orders.\n";
                    done = false;
                    break;
                }
                int adjNum;
                cout<<"Issuing Advance order\n";
                cout<<"Select Advance order type:\n";
                while(input){
                    cout<<"1) Attack 2) Defend\n";
                    int selection;
                    cin>>selection;

                    //Advance to attack enemy territory
                    if(selection == 1){
                        input = false;
                        vector <Territory*> attack = this->p->toAttack();
                        
                
                        cout<<"Please enter the territory you wish to advance army units to\n(select the number from your list of territories to attack): \n";
                        for(int i = 1; i<=attack.size();i++){
                            cout<<i<<") "<<*attack.at(i-1)->getTerritoryName()<<" ";
                        }
                        cout<<endl;
                        cin>>t_option;
       
                        cout<<"How many army units to advance to "<<*attack.at(t_option-1)->getTerritoryName()<<"?";
                        cout<<"\nEnter your selection: \n";
                        cin>>army;
                        //Find territories from where the player can advance army units to the selected territory
                        vector <Territory*> adj = attack.at(t_option-1)->getAdjTerritories();
                        vector <Territory*> select;
                        // vector <int> idx;
                        for(Territory* t: adj){
                            if((std::find(this->p->get_trt().begin(), this->p->get_trt().end(), t)) != this->p->get_trt().end()){
                                select.push_back(t);
                            //     auto it = std::find(this->p->get_trt().begin(), this->p->get_trt().end(), t);
                            //     idx.push_back(it - p->get_trt().begin());
                            }
                            else{
                                continue;
                            }
                        }
                        //If more than one adjacent territories owned by the player, ask from which territory to advance army units
                        if(select.size()>0){
            
                            cout<<"From which territory do you wish to advance the units ?\n";
                            for(int i = 1; i<=select.size();i++){
                                cout<<i<<") "<<*select.at(i-1)->getTerritoryName()<<" ";
                            }
                            while(input2){
                                cout<<"\nEnter your selection: ";
                                cin>>adjNum;
                                if(adjNum>select.size()){
                                    cout<<"Please select the correct option\n";
                                }
                                else{
                                    input2=false;
                                    Advance* a = new Advance(select.at(adjNum-1),attack.at(t_option-1),this->p,army);
                                    this->p->get_olst()->addOrder(a);
                                    issued_orders.push_back("Advance(Attack) | To: "+*attack.at(t_option-1)->getTerritoryName() + " | From: "+ *select.at(adjNum-1)->getTerritoryName() + "| "+ to_string(army)+" units");
                                    done = true;
                                }
                            }
                        }
                        //if only one adjacent territory is owned by the player, automatically issue advance order from the adjacent territory
                        else{
                            Advance* a = new Advance(attack.at(t_option-1), select.at(0),this->p,army);
                            this->p->get_olst()->addOrder(a);
                            issued_orders.push_back("Advance(Attack) | To: "+*attack.at(t_option-1)->getTerritoryName() + " | From: "+*select.at(0)->getTerritoryName() + "| "+ to_string(army)+" units");
                            done = true;
                        }
                    }

                    //Advance to defend territory
                    else if(selection == 2){
                        input = false;
                        vector <Territory*> defend = this->p->toDefend();
                        cout<<"Please enter the territory you wish to advance army units \n(select the number from your list of territories to defend): \n";
                        for(int i = 1; i<=defend.size();i++){
                            cout<<i<<") "<<*defend.at(i-1)->getTerritoryName()<<" ";
                        }
                        cin>>t_option;
                        cout<<"How many army units to advance to "<<*defend.at(t_option-1)->getTerritoryName()<<"?";
                        cout<<"\nEnter your selection: ";
                        cin>>army;
                        //Find territories from where the player can advance army units to the selected territory
                        vector <Territory*> adj = defend.at(t_option-1)->getAdjTerritories();
                        vector <Territory*> select;
                        for(Territory* t: adj){
                            if((std::find(this->p->get_trt().begin(), this->p->get_trt().end(), t)) != this->p->get_trt().end()){
                                select.push_back(t);
                            }
                            else{
                                continue;
                            }
                        }
                        //If more than one adjacent territories owned by the player, ask from which territory to advance army units
                        if(select.size()>1){
                            bool input2 = true;
                            
                            cout<<"From which territory do you wish to advance the units ?\n";
                            for(int i = 1; i<=select.size();i++){
                                cout<<i<<") "<<*select.at(i-1)->getTerritoryName()<<" ";
                            }
                            while(input2){
                                cout<<"\nEnter your selection: ";
                                cin>>adjNum;
                                if(adjNum>select.size()){
                                    cout<<"Please select the correct option\n";
                                }
                                else{
                                    input2=false;
                                    Advance* a = new Advance(defend.at(t_option-1), select.at(adjNum-1),this->p,army);
                                    this->p->get_olst()->addOrder(a);
                                    issued_orders.push_back("Advance(Attack) | To: "+*defend.at(t_option-1)->getTerritoryName() + " | From: "+*select.at(adjNum-1)->getTerritoryName() + "| "+ to_string(army)+" units");
                                    done = true;
                                }
                            }
                        }
                        //if only one adjacent territory is owned by the player, automatically issue advance order from the adjacent territory
                        else{
                            Advance* a = new Advance(defend.at(t_option-1), select.at(0),this->p,army);
                            this->p->get_olst()->addOrder(a);
                            issued_orders.push_back("Advance(Attack) | To: "+*defend.at(t_option-1)->getTerritoryName() + " | From: "+*select.at(0)->getTerritoryName() + "| "+ to_string(army)+" units");
                            done = true;
                        }
                    }
                    else{
                        cout<<"Please select the correct option\n";
                    }
                }

                break;//end of case Advance
            
            //case for Bomb order
            case 3:
                //verifying if all army units have been deployed
                if(deployed_unit < this->p->get_armyUnit()){
                    cout<<"Need to deploy all army units in the pool before issueing other orders.\n";
                    done = false;
                    break;
                }
                //if player has a bomb card, issue bomb order
                if(hasBomb){
                    cout<<"Issuing Bomb order\n";
                    vector <Territory*> attack = this->p->toAttack();
                        cout<<"Please select the target territory \n(select the number from your list of territories to attack): \n";
                        for(int i = 1; i<=attack.size();i++){
                            cout<<i<<") "<<*attack.at(i-1)->getTerritoryName()<<" ";
                        }
                    cout<<"\nEnter your selection: ";
                    cin>>option;

                    Bomb* b = new Bomb(attack.at(option-1), this->p);
                    this->p->get_olst()->addOrder(b);
                    issued_orders.push_back("Bomb | To: " + *attack.at(option-1)->getTerritoryName());
                    done=true;
                }
                //if player does not have a bomb card, return to previous selection
                else{
                    cout<<"Player does not have the right card to issue selected order.\nPlease select another option\n";
                    done = false;
                    break;
                }
                break;
            case 4:
                //verifying if all army units have been deployed
                if(deployed_unit < this->p->get_armyUnit()){
                    cout<<"Need to deploy all army units in the pool before issueing other orders.\n";
                    done = false;
                    break;
                }
                //if player has a blockade card, issue blockade order
                if(hasBlockade){
                    cout<<"Issuing Blockade order\n";
                    vector <Territory*> attack = this->p->toAttack();
                        cout<<"Please select the target territory \n(select the number from your list of territories to attack): \n";
                        for(int i = 1; i<=attack.size();i++){
                            cout<<i<<") "<<*attack.at(i-1)->getTerritoryName()<<" ";
                        }
                    cout<<"\nEnter your selection: ";
                    cin>>option;

                    Blockade* b = new Blockade(attack.at(option-1), this->p);
                    this->p->get_olst()->addOrder(b);
                    issued_orders.push_back("Blockade | To: " + *attack.at(option-1)->getTerritoryName());
                    done=true;
                }
                //if player does not have a blockade card, return to previous selection
                else{
                    cout<<"Player does not have the right card to issue selected order.\nPlease select another option\n";
                    done = false;
                    break;
                }
                break;
            case 5:
                //verifying if all army units have been deployed
                if(deployed_unit < this->p->get_armyUnit()){
                    cout<<"Need to deploy all army units in the pool before issueing other orders.\n";
                    done = false;
                    break;
                }
                //if player has a airlift card, issue airlift order
                if(hasAirlift){
                    cout<<"Issuing Airlift order\n";
                    vector <Territory*> owned = this->p->get_trt();
                    cout<<"Please select the source territory \n(select the number from your list of territories): \n";
                    for(int i = 1; i<=owned.size();i++){
                        cout<<i<<") "<<*owned.at(i-1)->getTerritoryName()<<" ";
                    }
                    while(input1){
                        cout<<"\nEnter your selection: ";
                        cin>>option;
                        if(option>owned.size()){
                            cout<<"Please select the correct option\n";
                        }
                        else{
                            input1 = false;
                        }
                    }

                    cout<<"Please select the target territory:\n";
                    vector<Territory*> attack = this->p->toAttack();
                    vector<Territory*> defend = this->p->toAttack();
                    for(int i=1; i<=attack.size();i++){
                        cout<<i<<") "<<*attack.at(i-1)->getTerritoryName()<<" ";
                    }
                    cout<<endl;
                    for(int j=1; j<=defend.size();j++){
                        cout<<attack.size()+j<<") "<<*defend.at(j-1)->getTerritoryName()<<" ";
                    }
                    while(input2){
                        cout<<"\nEnter your selection: ";
                        cin>>t_option;
                        if(t_option > attack.size()+defend.size()){
                            cout<<"Please select the correct option\n";
                        }
                        else{
                            input2 = false;
                        }
                    }
                    //determine target territory based on user input
                    Territory* target;
                    if(t_option <= attack.size()){
                        target = attack.at(t_option-1);
                    }
                    if(t_option > attack.size()){
                        target = defend.at(t_option-1);
                    }

                    cout<<"How many army units to airlift to "<<*target->getTerritoryName()<<"?";
                    cout<<"\nEnter your selection: ";
                    cin>>army;
                    Airlift* a = new Airlift(owned.at(option-1), target, this->p,army);
                    this->p->get_olst()->addOrder(a);
                    issued_orders.push_back("Airlift | From: " + *owned.at(option-1)->getTerritoryName() + " | To: "+*target->getTerritoryName()+" | " + to_string(army)+" units");
                    done=true;
                }
                //if player does not have a Airliftcard, return to previous selection
                else{
                    cout<<"Player does not have the right card to issue selected order.\nPlease select another option\n";
                    done = false;
                    break;
                }
                break;
            case 6:
                //verifying if all army units have been deployed
                if(deployed_unit < this->p->get_armyUnit()){
                    cout<<"Need to deploy all army units in the pool before issueing other orders.\n";
                    done = false;
                    break;
                }
                //if player has a diplomacy card, issue negotiate order
                if(hasDiplomacy){
                    cout<<"Issuing Negotiate order\n";
                    vector <Territory*> attack = p->toAttack();
                    vector <Player*> temp;
                    for (Territory* t: attack){
                        Player* p = t->getTerritoryOwner();
                        if((std::find(temp.begin(),temp.end(), p)) != temp.end()){
                            continue;
                        }
                        else{
                            temp.push_back(t->getTerritoryOwner());
                        }
                    }
                    
                    cout<<"Please select the target player \n(select the number the list of players): \n";
                    for(int i = 1; i<=temp.size();i++){
                        cout<<i<<") "<<temp.at(i-1)->get_name()<<" ";
                    }
                    while(input){
                        cout<<"\nEnter your selection: ";
                        cin>>option;
                        if(option > temp.size()){
                            cout<<"Please select the correct option";
                        }
                        else{
                            input = false;
                        }
                    }
                    
                    Player* target = temp.at(option-1);
                    Negotiate* n = new Negotiate(this->p, target);
                    this->p->get_olst()->addOrder(n);
                    issued_orders.push_back("Negotiate| Target: " + target->get_name());
                    done=true;
                }
                //if player does not have a blockade card, return to previous selection
                else{
                    cout<<"Player does not have the right card to issue selected order.\nPlease select another option\n";
                    done = false;
                    break;
                }
                break;
        }//end of switch
    }//end of while
    

    cout << "Issued Orders:" << endl;
    for (string order:issued_orders){
        cout<<order<<endl;
    }
    
    bool issueMore = false;
    string yn;
    cout<<"Do you wish to issue more orders? (Y/N)\n";
    cin>>yn;
    if(yn == "Y" || yn == "y"){
        issueMore = true;
    }
    else if(yn == "N" || yn == "n"){
        issueMore = false;
    }
    else{
        cout<<"Wrong input. Will issue order on the next turn\n";
        issueMore = true;
    }

    return issueMore;
}

//-----------------------------------//
// BENEVOLENT PLAYER IMPLEMENTATION  //
//-----------------------------------//

// Constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p): PlayerStrategy(p) {}

// Destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

// toAttack 
// Benevolent players never issue any orders to enemy countries, thus, we do not need a list of territories to be attacked
std::vector <Territory*> BenevolentPlayerStrategy::toAttack()
{
    return vector<Territory*>{};
}

// toDefend 
// Benevolent players needs to know which territories to defend to issue orders
std::vector <Territory*> BenevolentPlayerStrategy::toDefend()
{
    vector<Territory*> trt = this->p->get_trt();
    
    //new vector of Territory to be returned as result
    std::vector <Territory*> result_defend; 

    for (Territory* t : trt){
        
        //traverse the list of adjacent territories for each t 
        for(Territory* t_adj: t->getAdjTerritories()){
            //verify if each territory in the adjacent territories list is in the list of territories owned
            
            //The adjacent territory was found in the list of owned territories
            //We don't need to defend the territory t           
            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end()){
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

// issueOrder (How does a neutral player decide which order to issue)
bool BenevolentPlayerStrategy::issueOrder() { 

    //List of territories to be defended
    vector <Territory*> defend = p->toDefend();
    
    //storing army units deployed in each territory to be defended
    vector <int> def_army;
    for(Territory* t: defend){
        def_army.push_back(*t->getArmy());
    }

    //Variable to store orders to be displayed
    vector <string> issued_orders;

    //Issue Deploy order
    bool deploy = false;

    // keep track of units deployed previously
    int deployed_unit = 0;

    for (Order* o : this->p->get_olst()->getOrder())
    {
        // If this order is of type Deploy
        if (o->getType() == "Deploy" || o->getType() == "deploy")
        {
            // Increment deployed_units var
            Deploy *d = (Deploy *) o;
            deployed_unit = deployed_unit+d->getNumberUnits();
        }
    }

    //deploy = true => done issuing Deploy order
    if(deployed_unit == p->get_armyUnit()){
        deploy = true;
    }
    else{
        int max;
        max = *max_element(def_army.begin(), def_army.end());
        //if all territory have 0 army units select the territory to issue deploy order randomly
        if(max == 0){
            int idx = rand()%def_army.size();
            int army = 1 + rand()%(p->get_armyUnit() - deployed_unit - 1);
            def_army.at(idx) = army;
            Deploy* d = new Deploy(defend.at(idx), this->p, army);
            this->p->get_olst()->addOrder(d);
            issued_orders.push_back("Deploy | To: " + *defend.at(idx)->getTerritoryName() + " | " + to_string(army) + " units");
        }

        //if some territories have army units, determine the ones that have the least
        if(max > 0){

            int min = *min_element(def_army.begin(), def_army.end());
                
            //find the indexes of territories with the lowest army unit number
            vector <int> idx_arr;
            for(int i = 0; i<def_army.size(); i++){
                if(min == def_army.at(i)){
                    idx_arr.push_back(i);
                }
            }

            //randomly select from the indexes of territories with lowest army units to deploy armies
            int idx = rand()%idx_arr.size();
            int army = 1 + rand()%(p->get_armyUnit() - 1);
            def_army.at(idx_arr.at(idx)) = army;
            Deploy* d = new Deploy(defend.at(idx_arr.at(idx)), this->p, army);
            this->p->get_olst()->addOrder(d);
            issued_orders.push_back("Deploy | To: " + *defend.at(idx_arr.at(idx))->getTerritoryName() + " | " + to_string(army) + " units");
        }
    }
    //end of while case Deploy order

    //Issue Advance order
    //Weakest territory = territory with the lowest army units in the list of territories to be defended
    if(deploy){
        //get the number of units currently in each territory to be defended 
        vector <int> unitInTrt;
        vector <string> trt_name;
        for (Territory* t: p->toDefend()){
            unitInTrt.push_back(*t->getArmy());
            trt_name.push_back(*t->getTerritoryName());
        }

        //add the number of units deployed in the current order list
        for (Order* o : this->p->get_olst()->getOrder()){
            //
            if (o->getType() == "Deploy" || o->getType() == "deploy")
            {
                Deploy *d = (Deploy *) o;
                string tg = *d->getTarget()->getTerritoryName();

                //find the index of the territory that was targetted for deploy order
                int idx;
                for(int i = 0; i<trt_name.size(); i++){
                    if (trt_name.at(i) == tg){
                        idx = i;
                        break;
                    }
                }
                
                //locally change the number of units associated for target territory
                unitInTrt.at(idx) = unitInTrt.at(idx) + d->getNumberUnits();
            }
        }

        //find the min army units associated with each territories
        int minArmy = *min_element(unitInTrt.begin(), unitInTrt.end());
        int maxArmy = *max_element(unitInTrt.begin(), unitInTrt.end());

        //find the indexes of territories with the lowest army unit number
        vector <int> idx_min;
        for(int i = 0; i<unitInTrt.size(); i++){
            if(minArmy == unitInTrt.at(i)){
                idx_min.push_back(i);
            }
        }

        //randomly select from the indexes of territories with lowest army units to deploy armies
        int j = rand()%idx_min.size();

        //randomly select a source territory
        int k = rand()%p->get_trt().size();

        //randomly select from the army units to dispatch based on the max army units in current list of territories
        int army = 1 + rand()%(maxArmy - 1);
        
        Advance* a = new Advance(p->get_trt().at(k), p->toDefend().at(j), p, army);
        this->p->get_olst()->addOrder(a);
        issued_orders.push_back("Advance | To: " + *p->toDefend().at(j)->getTerritoryName() + " | " + to_string(army) + " units");

    }

    //print out the order issued
    for(string s:issued_orders){
        cout<<s<<endl;
    }

    return (rand() % 100) < 60;
}





//-----------------------------------//
// Cheater PLAYER IMPLEMENTATION     //
//-----------------------------------//


CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p): PlayerStrategy(p), previousArmyNumber(0) {}
CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

bool CheaterPlayerStrategy::issueOrder() {
    // CHECK if the turn has started by using the reinforcement phase
    if (p->get_armyUnit() > previousArmyNumber) {
        // If the player has more armies, then store the new
        // amount and continue with the 'order' (ie cheat)
        previousArmyNumber = p->get_armyUnit();
    } else {
        // If a new turn hasn't started yet, do not issue
        // an 'order' (ie cheat)
        return false;
    }

    // The CheaterPlayerStrategy straight up conquers adjacent territories
    vector <Territory*> result_attack = toAttack();
    for (Territory* t: result_attack) {
        cout << "Taking territory " << *(t->getTerritoryName()) << endl;
        Player *oldOwner = t->getTerritoryOwner();
        // Make ourselves owner
        t->setTerritoryOwner(p);

        vector<Territory*> ownedTerritories = p->get_trt();
        ownedTerritories.push_back(t);
        p->set_Trt(ownedTerritories);
        
        // Remove ownership from other player
        vector<Territory*> oldOwnerTerritories = oldOwner->get_trt();

        for (auto it = oldOwnerTerritories.begin(); it < oldOwnerTerritories.end(); ++it) {
            if (*it == t) {
                oldOwnerTerritories.erase(it);
                break;
            }
        }
        
        oldOwner->set_Trt(oldOwnerTerritories);
    }
    // The cheater player only takes territory once per turn
    return false;
}


std::vector <Territory*> CheaterPlayerStrategy::toAttack() {
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

// The CheaterPlayerStrategy never defends, so this is not needed
std::vector <Territory*> CheaterPlayerStrategy::toDefend() {
    return vector<Territory*>{};
}