#include <iostream> 
#include <algorithm>
#include <vector>
#include <sstream>
#include "Orders.h"
#include "Map.h"
#include "Player.h"
#include "LoggingObserver.h"

using std::cout;
using std::string; 
using std::vector;
using std::endl;

//OrdersList class
//OrdersList default constructor
OrdersList::OrdersList(){
    std::vector<Order *> orderList;
    this->orderList = orderList;
}

//OrdersList paramatrized constructor
OrdersList::OrdersList(std::vector<Order*> orderList){
    this->orderList = orderList;
}

//OrdersList copy constructor copies the orders from the other list
OrdersList::OrdersList(const OrdersList& ol1){
    orderList = vector<Order*>();
    for (Order* c: ol1.orderList) {
        orderList.push_back(c->clone());
    }}

//OrdersList destructor
OrdersList::~OrdersList(){
    //delete all the Order objects from the list
    for (int i = 0; i < this->orderList.size(); i++)
	{
		delete this->orderList.at(i);
	}
}

//OrdersList assignment operator to copy the orders over
OrdersList& OrdersList::operator=(const OrdersList& ol) {
	orderList = vector<Order*>();
    for (Order* c: ol.orderList) {
        orderList.push_back(c->clone());
    }
    return *this;
}

//Setter method for OrdersList 
void OrdersList::setOrder(std::vector<Order*> order){
    this->orderList = order;
}

//Getter method for OrdersList
std::vector<Order*>& OrdersList::getOrder(){
    return this->orderList;
}

//Add an order to the Order list
void OrdersList::addOrder(Order* order){
    this->orderList.push_back(order);
    notify(this);
}

//Remove an order from the Order list
void OrdersList::remove(Order* order){
    //find the position of the order in the list
    std::vector<Order*>::iterator x;
    x = find(orderList.begin(), orderList.end(), order);
    int x1 = distance(orderList.begin(), x);
    int* i = &x1;
    //if the position is within the bounds, remove the order
    if(*i >= 0 || *i < orderList.size()){
        this->orderList.erase(orderList.begin() + *i);
    }
    else{
        cout << "ERROR: Index out of bounds" << endl;
        return;
    }
}

//Move an Order to position "index" in the Order list
void OrdersList::move(Order* order, int index){
    //check if index is within the bounds of the list
    if(index >= 0 || index < orderList.size()){
        //find the current position of the order
        std::vector<Order*>::iterator x;
        x = find(orderList.begin(), orderList.end(), order);
        int x1 = distance(orderList.begin(), x);
        int* i = &x1;
        //if the position is within the bounds, move the order to index
        if(*i >= 0 || *i < orderList.size()){
            Order* tempOrder = orderList.at(*i);
            orderList.erase(orderList.begin() + *i);
            orderList.insert(orderList.begin() + index, tempOrder);
        }
    }
    else{
        cout << "ERROR: Index out of bounds" << endl;
        return;
    }
}

//Get the index of a given order
int OrdersList::getIndex(Order * order){
    std::vector<Order*>::iterator x;
    x = find(orderList.begin(), orderList.end(), order);
    return distance(orderList.begin(), x);
}

//Output stream
std::ostream& operator<<(std::ostream &strm, const OrdersList &ol){
    // strm << "Order List: ";
    // for (int i = 0; i < ol.orderList.size(); i++) {
    //     // Order& orderRef = *(ol.orderList.at(i));
    //     strm << *(ol->getOrder().at(i));
    //     if (i < ol.orderList.size() - 1) {
    //         strm << ", ";
    //     }
    // }
    strm<<"{";
    for(Order* o: ol.orderList){
        strm<<*o<<" ";
    }
    strm<<"}";
    return strm;
   
}

// Method providing the string to log
string OrdersList::stringToLog() {
    std::stringstream out;
    out << *this;
    return out.str();
}



//Order class
//Order default constructor
Order::Order(){
    type = "";
    effect = "";
    hasExecuted = false;
}

//Order paramatrized constructor
Order::Order(std::string type){
    this->type = type;
    effect = "";
    hasExecuted = false;
}

//Order paramatrized constructor
Order::Order(std::string type, std::string effect){
    this->type = type;
    this ->effect = effect;
}

//Order copy constructor
Order::Order(const Order& o1){
    this->type = o1.type;
    this->effect = o1.effect;
}

//Order destructor
Order::~Order(){

}

//Order assignment operator
Order& Order::operator=(const Order& o){
	this->type = o.type;
    this->effect = o.effect;
	return *this;
}

//Getter for type
std::string Order::getType(){
    return this->type;
}

//Setter for type
void Order::setType(std::string type){
    this->type = type;
}

//Getter for effect
std::string Order::getEffect(){
    return this->effect;
}

//setter for effect
void Order::setEffect(std::string effect){
    this->effect = effect;
}

//getter for hasExecuted
bool Order::getHasExecuted(){
    return this->hasExecuted;
}
//Setter for hasExecuted
void Order::setHasExecuted(bool hasExecuted){
    this->hasExecuted = hasExecuted;
}

 //Order input stream
 std::istream& operator >> (std::istream& in, Order& order){
    std::cout << "Enter your order: ";
    in >> order.type;
    return in;
}

//Order output stream
std::ostream& operator<<(std::ostream &strm, const Order &order){
    if(!order.hasExecuted){
        return strm << "Order(" << order.type << ")";
    }
    else{
        return strm << "Order(" << order.type << "," << order.effect << ")";
    }
}

// Method providing the string to log
std::string Order::stringToLog() {
    if (effect.length() == 0) {
        return string("Order ").append(type).append(" has not executed yet");
    } else {
        return string("Command effect: ").append(effect);
    }
}



//class Deploy
//Deploy default constructor
Deploy::Deploy(): Order("Deploy"), target(nullptr), player(nullptr), numberUnits(0) {
    this->type = "Deploy";
}

Deploy::Deploy(Territory *target, Player *player, int numberUnits): 
    Order("Deploy"), target(target), player(player), numberUnits(numberUnits) {
}

//Deploy destructor
Deploy::~Deploy(){

}

//Deploy copy constructor
Deploy::Deploy(const Deploy& d1):
    Order(d1.type, d1.effect), target(d1.target), player(player), numberUnits(d1.numberUnits) {
}

//Deploy assignment operator
Deploy& Deploy::operator=(const Deploy& d1){
	Order::operator=(d1);
    this->target = d1.target;
    this->player = d1.player;
    this->numberUnits = d1.numberUnits;
	return *this;
}

//Deploy output stream
std::ostream& operator<<(std::ostream &strm, const Deploy &Deploy){
    if(!Deploy.hasExecuted){
        return strm << "Deploy(" << Deploy.type << ")";
    }
    else{
        return strm << "Deploy(" << Deploy.type << "," << Deploy.effect << ")";
    }
}

int Deploy::getNumberUnits()
{
    return this->numberUnits;
}

//Validate if the order is valid
bool Deploy::validate(){
    vector<Territory*> trt = player->get_trt();
    bool ownsTerritory = any_of(trt.begin(), trt.end(), [this](Territory *t){return t == this->target;});
    bool haveEnoughUnits = player->get_armyUnit() >= numberUnits;
    return ownsTerritory && haveEnoughUnits;
}

//execute order
void Deploy::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect.append("Executed Deploy order, adding ").append(std::to_string(numberUnits)).append(" units to the territory ").append(*(target->getTerritoryName()));
        // Increment the amount of army units in the target
        int *targetArmies = target->armyAmount;
        (*targetArmies) += numberUnits;
        // Decrement the amount of army units the player has
        player->set_armyUnit(player->get_armyUnit() - numberUnits);
        
    }
    else{
        this->hasExecuted = false;
        effect.append("Deploy cannot be executed");
        cout << "ERROR: Deploy cannot be executed" << endl;
    }
    notify(this);
}

//clone method
Order* Deploy::clone(){
    return new Deploy(*this);
}


//class Advance
//Advance default constructor
Advance::Advance(): target(nullptr), source(nullptr), player(nullptr), numberUnits(0) {
    type = "Advance";
}

Advance::Advance(Territory *source, Territory *target, Player *player, int numberUnits): 
    source(source), target(target), player(player), numberUnits(numberUnits) {
}

//Advance destructor
Advance::~Advance(){

}

//Advance copy constructor
Advance::Advance(const Advance& ad1):
    Order(ad1.type, ad1.effect), source(ad1.source), target(ad1.target), player(player), numberUnits(ad1.numberUnits){
}

//Advance assignment operator
Advance& Advance::operator=(const Advance& ad){
	Advance::operator=(ad);
    this->source = ad.source;
    this->target = ad.target;
    this->player = ad.player;
    this->numberUnits = ad.numberUnits;
	return *this;
}

//Advance output stream
std::ostream& operator<<(std::ostream &strm, const Advance &Advance){
    if(!Advance.hasExecuted){
        return strm << "Advance(" << Advance.type << ")";
    }
    else{
        return strm << "Advance(" << Advance.type << "," << Advance.effect << ")";
    }
}

//Validate if the order is valid
bool Advance::validate()
{
    // Get territories owned by player and save them into playerTerritories vector
    vector<Territory*> playerTerritories = player->get_trt();
    
    // Check if source territory belongs to player
    bool ownsSource = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->source;});
    
    // Check if target territory is adjacent to source
    bool isTargetAdjacent = false;

    for (auto i : source->AdjTerritories)
    {
        if (i==target)
        {
            isTargetAdjacent = true;
            break;
        }
    }

    bool negotiationBlocks = false;
    // Check to see if a negotiate order is blocking advance (which might be an attack)
    if (player != target->getTerritoryOwner()) {
        // If the target is not player-owned, this is an attack: check for negotiation
        Player *enemy = target->getTerritoryOwner();
        negotiationBlocks = enemy->hasNegotiationWith(player);
    }

    // Check if source territory possesses enough troops for request
    bool enoughTroops = this->numberUnits <= *source->armyAmount;

    return ownsSource && isTargetAdjacent && enoughTroops && !negotiationBlocks;
}

// isAttack method to check if the advance order is an attack or not
bool Advance::isAttack()
{
    // Get territories owned by player and save them into playerTerritories vector
    vector<Territory*> playerTerritories = this->getPlayer()->get_trt();
    
    // Check if target territory belongs to player
    return !any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->target;});
}

// Getter for target
Territory* Advance::getTarget()
{
    return this->target;
}

// Getter for player
Player* Advance::getPlayer()
{
    return this->player;
}

//execute order
void Advance::execute(){
    //validate the order then execute
    if(validate())
    {
        this->hasExecuted = true;
        effect = "executed";

        // Save number of units sent to separate variable
        int attackerNb = this->numberUnits;

        // Get territories owned by player and save them into playerTerritories vector
        vector<Territory*> playerTerritories = player->get_trt();
        
        // Check if source territory belongs to player
        bool ownsSource = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->source;});
        
        // Check if target territory belongs to player
        bool ownsTarget = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->target;});

        // If player owns source and target, move units
        if (ownsSource && ownsTarget)
        {
            // Increment target territory with army amount
            int newTargetArmy = (*(target->getArmy())+this->numberUnits);
            int* ptrTargetArmy = &newTargetArmy;
            target->setArmy(ptrTargetArmy);

            // Decrement source territory with army amount
            int newSourceArmy = (*(source->getArmy())-this->numberUnits);
            int* ptrSourceArmy = &newSourceArmy;
            source->setArmy(ptrSourceArmy);
        }
        // If player does not own target, attack target
        else
        {
            // Decrement source territory with army amount
            int newSourceArmy = (*(source->getArmy())-this->numberUnits);
            int* ptrSourceArmy = &newSourceArmy;
            source->setArmy(ptrSourceArmy);
            
            // While attacker or defender doesn't have 0 units...
            while (attackerNb!=0 && *(this->target->getArmy())!=0)
            {
                // Counters to keep track of losses
                int attackerLosses = 0;
                int defenderLosses = 0;

                // For every attacking unit, increment defenders loss with probability
                for (int i = 0; i < attackerNb; i++)
                {
                    bool kill = (rand() % 100) < 60;
                    if (kill)
                    {
                        defenderLosses++;
                    }
                }

                // For every defending unit, increment attackers loss with probability
                int *targetArmy = target->getArmy();
                for (int i = 0; i < *targetArmy; i++)
                {
                    bool kill = (rand() % 100) < 70;
                    if (kill)
                    {
                        attackerLosses++;
                    }
                }

                // Decrement source army and target territory army with their losses
                attackerNb = attackerNb - attackerLosses;
                int newTargetArmy = (*(target->getArmy())-defenderLosses);
                int* ptrTargetArmy = &newTargetArmy;
                target->setArmy(ptrTargetArmy);

                // Check for negative values and set them to zero for attacker and defender
                if (attackerNb < 0)
                {
                    attackerNb = 0;
                }

                if (*this->target->getArmy() < 0)
                {
                    newTargetArmy = 0;
                    target->setArmy(ptrTargetArmy);
                }
            }
            // If attacker won, capture territory
            if (attackerNb!=0 && *target->getArmy()==0)
            {
                // Save territory vector of attacker
                vector<Territory*> attackerTerritories = this->player->get_trt();

                // Add conquered territory in attacker's territory vector
                attackerTerritories.push_back(this->target);

                // Save territory vector of defender
                vector<Territory*> defenderTerritories = this->target->getTerritoryOwner()->get_trt();

                // Remove conquered territory in defender's territory vector
                for (auto it = defenderTerritories.begin(); it != defenderTerritories.end(); ++it)
                {
                    Territory *aTerritory = *it;
                    // If both point to the same territory, remove it from defender list
                    if(aTerritory == this->target)
                    {
                        defenderTerritories.erase(it);
                        break;
                    }
                }
                
                // Change owned territories of attacker
                this->player->set_Trt(attackerTerritories);

                // Change owned territories of defender
                this->target->getTerritoryOwner()->set_Trt(defenderTerritories);

                // Change ownership of territory
                this->target->setTerritoryOwner(this->player);

                // Surviving army units occupy conquered territory
                this->target->setArmy(&attackerNb);
            }
        }
        // cout << "Deploy has executed" << endl;
    }
    else{
        this->hasExecuted = false;
        effect.append("Advance cannot be executed");
        cout << "ERROR: Advance cannot be executed" << endl;
    }
    notify(this);
}

//clone method
Order* Advance::clone(){
    return new Advance(*this);
}

//class Bomb
//Bomb default constructor
Bomb::Bomb(): Order("Bomb"), target(nullptr), player(nullptr) {
    this->type = "Bomb";
}

Bomb::Bomb(Territory *target, Player *player): 
    Order("Bomb"), target(target), player(player) {
}

//Bomb destructor
Bomb::~Bomb(){

}

//Bomb copy constructor
Bomb::Bomb(const Bomb& b1):
    Order(b1.type, b1.effect), target(b1.target), player(player) {
}

//Bomb assignment operator
Bomb& Bomb::operator=(const Bomb& b){
	Bomb::operator=(b);
    this->target = b.target;
    this->player = b.player;
	return *this;
}

//Bomb output stream
std::ostream& operator<<(std::ostream &strm, const Bomb &Bomb){
    if(!Bomb.hasExecuted){
        return strm << "Bomb(" << Bomb.type << ")";
    }
    else{
        return strm << "Bomb(" << Bomb.type << "," << Bomb.effect << ")";
    }
}

//Validate if the order is valid
bool Bomb::validate()
{
    // Save player territories into vector
    vector<Territory*> playerTerritories = player->get_trt();

    // Check if the enemy has a negotiation that would block the bombing
    Player *enemy = target->getTerritoryOwner();
    bool negotiationBlocks = enemy->hasNegotiationWith(player);

    // Check if target territory belongs to player
    bool ownsTarget = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->target;});

    // Check if target territory is adjacent to source
    bool isTargetAdjacent = false;

    for (auto i : playerTerritories)
    {
        for (auto j : i->AdjTerritories)
        {
            if (j==target)
            {
                isTargetAdjacent = true;
                goto DONE;
            }
        }
    }

    DONE: return !ownsTarget&&isTargetAdjacent && !negotiationBlocks;
}

//execute order
void Bomb::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect = "executed";

        // Remove half of the army units from target territory
        *(this->target->armyAmount) = *(this->target->armyAmount)/2;

        cout << "Bomb has executed" << endl;
    }
    else{
        this->hasExecuted = false;
        effect.append("Bomb cannot be executed");
        cout << "ERROR: Bomb cannot be executed" << endl;
    }
    notify(this);
}

//clone method
Order* Bomb::clone(){
    return new Bomb(*this);
}


//class Blockade
//Blockade default constructor
Blockade::Blockade(){
    type = "Blockade";

}

//Blockade paramaterized constructor
Blockade::Blockade(Territory *target, Player *player):
    Order("Blockade"), target(target), player(player) {
}

//Blockade destructor
Blockade::~Blockade(){

}

//Blockade copy constructor
Blockade::Blockade(const Blockade& bl1):
    Order(bl1.type, bl1.effect), target(bl1.target), player(bl1.player) {
}

//Blockade assignment operator
Blockade& Blockade::operator=(const Blockade& bl){
	Blockade::operator=(bl);
    this->target = bl.target;
    this->player = bl.player;
	return *this;
}

//Blockade output stream
std::ostream& operator<<(std::ostream &strm, const Blockade &Blockade){
    if(!Blockade.hasExecuted){
        return strm << "Blockade(" << Blockade.type << ")";
    }
    else{
        return strm << "Blockade(" << Blockade.type << "," << Blockade.effect << ")";
    }
}

//Validate if the order is valid
bool Blockade::validate(){
    // Save player territories into vector
    vector<Territory*> playerTerritories = player->get_trt();
    
    // Check if target territory belongs to player
    bool ownsTarget = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->target;});

    return ownsTarget;
}

//execute order
void Blockade::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect = "executed";

        // Double units in territory
        *(this->target->armyAmount) = *(this->target->armyAmount)*2;
        
        // Save territory vector of player
        vector<Territory*> playerTerritories = this->player->get_trt();

        // Remove blockaded territory from player's territory vector
        for (auto it = playerTerritories.begin(); it != playerTerritories.end(); ++it)
        {
            Territory *aTerritory = *it;
            // If both point to the same territory, remove it from territory list
            if(aTerritory == this->target)
            {
                playerTerritories.erase(it);
                break;
            }
        }

        // Change owned territories of player
        this->player->set_Trt(playerTerritories);

        // Change ownership of territory
        this->target->setTerritoryOwner(new Player("Neutral Player", {this->target}, nullptr, {}));
    }
    else{
        this->hasExecuted = false;
        effect.append("Blockade cannot be executed");
        cout << "ERROR: Blockade cannot be executed" << endl;
    }
    notify(this);
}

//clone method
Order* Blockade::clone(){
    return new Blockade(*this);
}

//class Airlift
//Airlift default constructor
Airlift::Airlift(){
    type = "Airlift";
}

//Airlift paramaterized constructor
Airlift::Airlift(Territory *source, Territory *target, Player *player, int numToMove):
    Order("Airlift"), source(source), target(target), player(player), numToMove(numToMove) {
}

//Airlift destructor
Airlift::~Airlift(){

}

//Airlift copy constructor
Airlift::Airlift(const Airlift& ai1): 
    Order(ai1.type, ai1.effect), source(ai1.source), target(ai1.target), 
    player(ai1.player), numToMove(ai1.numToMove) {
}

//Validate if the order is valid
bool Airlift::validate(){
    vector<Territory*> playerTerritories = player->get_trt();
    
    // Check if source territory belongs to player
    bool ownsSource = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->source;});
    bool ownsTarget = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->target;});
    bool enoughArmies = *(source->armyAmount) >= numToMove;
    return ownsSource && ownsTarget && enoughArmies;
}

//execute order
void Airlift::execute(){
    if(validate()){
        this->hasExecuted = true;
        (*source->armyAmount) -= numToMove;
        (*target->armyAmount) += numToMove;
        effect.append("Executed Airlift order, moving ").append(to_string(numToMove))
                .append(" units from ").append(*source->getTerritoryName()).append(" to ")
                .append(*target->getTerritoryName());
    } else {
        this->hasExecuted = false;  
        effect.append("Airlift order cannot be executed");
    }
    notify(this);
}

//Airlift assignment operator
Airlift& Airlift::operator=(const Airlift& ai){
	Order::operator=(ai);
    this->source = ai.source;
    this->target = ai.target;
    this->player = ai.player;
    this->numToMove = ai.numToMove;
	return *this;
}

//Airlift output stream
std::ostream& operator<<(std::ostream &strm, const Airlift &Airlift){
    return strm << "Airlift order of " << Airlift.numToMove <<  " armies from territory "
     << *Airlift.source << " to " << *Airlift.target;
    /*if(!Airlift.hasExecuted){
        return strm << "Airlift(" << Airlift.type << ")";
    }
    else{
        return strm << "Airlift(" << Airlift.type << "," << Airlift.effect << ")";
    }*/
}

//clone method
Order* Airlift::clone(){
    return new Airlift(*this);
}


//class Negotiate
//Negotiate default constructor
Negotiate::Negotiate(): Order("negotiate") {
}

// Negotiate paramaterized constructor
Negotiate::Negotiate(Player *source, Player *target):
    Order("Negotiate"), source(source), target(target) {
}

//Negotiate destructor
Negotiate::~Negotiate(){

}

//Negotiate copy constructor
Negotiate::Negotiate(const Negotiate& n1): Order(n1.type), source(source), target(target) {
}

//Negotiate assignment operator
Negotiate& Negotiate::operator=(const Negotiate& n){
	Order::operator=(n);
    source = n.source;
    target = n.target;
	return *this;
}

//Negotiate output stream
std::ostream& operator<<(std::ostream &strm, const Negotiate &Negotiate){
    if(!Negotiate.hasExecuted){
        return strm << "Negotiate(" << Negotiate.type << ")";
    }
    else{
        return strm << "Negotiate(" << Negotiate.type << "," << Negotiate.effect << ")";
    }
}

//Validate if the order is valid
bool Negotiate::validate() {
    bool isNeutral = this->target->get_name() == "Neutral Player";
    // The order is valid as long as the two 
    // players it's between are different
    return (source != target) && !isNeutral;
}

//execute order
void Negotiate::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect.append("Negotiation between ").append(source->get_name()).append(" and ").append(target->get_name()).append(" executed ");
        source->addNegotiatedPlayer(target);
        target->addNegotiatedPlayer(source);
    } else {
        this->hasExecuted = false;
        effect.append("Negotiate order cannot be executed");
    }
    notify(this);
}

//clone method
Order* Negotiate::clone(){
    return new Negotiate(*this);
}

