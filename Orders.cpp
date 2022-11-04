#include <iostream> 
#include <algorithm>
#include "Orders.h"
#include "Map.h"
#include "Player.h"

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
    strm << "Order List: ";
    for (int i = 0; i < ol.orderList.size(); i++) {
        Order& orderRef = *(ol.orderList[i]);
        strm << orderRef;
        if (i < ol.orderList.size() - 1) {
            strm << ", ";
        }
    }
    return strm;
   
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

//Oorder output stream
std::ostream& operator<<(std::ostream &strm, const Order &order){
    if(!order.hasExecuted){
        return strm << "Order(" << order.type << ")";
    }
    else{
        return strm << "Order(" << order.type << "," << order.effect << ")";
    }
}



//class Deploy
//Deploy default constructor
Deploy::Deploy(): target(nullptr), player(nullptr), numberUnits(0) {
    this->type = "Deploy";
}

Deploy::Deploy(Territory *target, Player *player, int numberUnits): 
    target(target), player(player), numberUnits(numberUnits) {
}

//Deploy destructor
Deploy::~Deploy(){

}

// TODO
//Deploy copy constructor
Deploy::Deploy(const Deploy& d1){
    this->type = d1.type;
    this->effect = d1.effect;
}

// TODO
//Deploy assignment operator
Deploy& Deploy::operator=(const Deploy& d1){
	Order::operator=(d1);
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
        effect = "executed";
        int * targetArmies = target->armyAmount;
        // Increment the amount of target armies
        (*targetArmies)++; 
        cout << "Deploy has executed" << endl;
    }
    else{
        this->hasExecuted = false;
        cout << "ERROR: Deploy cannot be executed" << endl;
    }
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
Advance::Advance(const Advance& ad1){
    this->type = ad1.type;
    this->effect = ad1.effect;
}

//Advance assignment operator
Advance& Advance::operator=(const Advance& ad){
	Advance::operator=(ad);
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

    // Check if source territory possesses enough troops for request
    bool enoughTroops = this->numberUnits <= *source->armyAmount;

    return ownsSource && isTargetAdjacent && enoughTroops;
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
            target->armyAmount = target->armyAmount+this->numberUnits;

            // Decrement source territory with army amount
            source->armyAmount = source->armyAmount-this->numberUnits;
        }
        // If player does not own target, attack target
        else
        {
            // While attacker or defender doesn't have 0 units...
            while (attackerNb!=0 || this->target->armyAmount!=0)
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
                for (int i = 0; i < *target->armyAmount; i++)
                {
                    bool kill = (rand() % 100) < 70;
                    if (kill)
                    {
                        attackerLosses++;
                    }
                }

                // Decrement source army and target territory army with their losses
                attackerNb = attackerNb - attackerLosses;
                this->target->armyAmount = this->target->armyAmount - defenderLosses;

                // Check for negative values and set them to zero for attacker and defender
                if (attackerNb < 0)
                {
                    attackerNb = 0;
                }

                if (*this->target->armyAmount < 0)
                {
                    this->target->armyAmount = 0;
                }
            }
        }
        cout << "Deploy has executed" << endl;
    }
    else{
        this->hasExecuted = false;
        cout << "ERROR: Advance cannot be executed" << endl;
    }
}

//clone method
Order* Advance::clone(){
    return new Advance(*this);
}

//class Bomb
//Bomb default constructor
Bomb::Bomb(){
    type = "Bomb";
    valid = true;
}

//Bomb destructor
Bomb::~Bomb(){

}

//Bomb copy constructor
Bomb::Bomb(const Bomb& b1){
    this->type = b1.type;
    this->effect = b1.effect;
}

//Bomb assignment operator
Bomb& Bomb::operator=(const Bomb& b){
	Bomb::operator=(b);
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
bool Bomb::validate(){
    if (valid){
        cout << "Bomb is valid" << endl;
        return true;
    }
    else{
        cout << "ERROR: Bomb is not valid" << endl;
        return false;
    }
}

//execute order
void Bomb::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect = "executed";
        cout << "Bomb is executing" << endl;
    }
    else{
        this->hasExecuted = false;
        cout << "ERROR: Bomb cannot be executed" << endl;
    }
}

//getter for valid
bool Bomb::getValid(){
    return this->valid;
}

//setter for valid
void Bomb::setValid(bool valid){
    this->valid = valid;
}

//clone method
Order* Bomb::clone(){
    return new Bomb(*this);
}


//class Blockade
//Blockade default constructor
Blockade::Blockade(){
    type = "Blockade";
    valid = true;
}

//Blockade destructor
Blockade::~Blockade(){

}

//Blockade copy constructor
Blockade::Blockade(const Blockade& bl1){
    this->type = bl1.type;
    this->effect = bl1.effect;
}

//Blockade assignment operator
Blockade& Blockade::operator=(const Blockade& bl){
	Blockade::operator=(bl);
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
    if (valid){
        cout << "Blockade is valid" << endl;
        return true;
    }
    else{
        cout << "ERROR: Blockade is not valid" << endl;
        return false;
    }
}

//execute order
void Blockade::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect = "executed";
        cout << "Blockade is executing" << endl;
    }
    else{
        this->hasExecuted = false;
        cout << "ERROR: Blockade cannot be executed" << endl;
    }
}

//getter for valid
bool Blockade::getValid(){
    return this->valid;
}

//setter for valid
void Blockade::setValid(bool valid){
    this->valid = valid;
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
    source(source), target(target), player(player), numToMove(numToMove) {
}

//Airlift destructor
Airlift::~Airlift(){

}

// TODO
//Airlift copy constructor
Airlift::Airlift(const Airlift& ai1){
    this->type = ai1.type;
    this->effect = ai1.effect;
}

//Validate if the order is valid
bool Airlift::validate(){
    vector<Territory*> playerTerritories = player->get_trt();
    
    // Check if source territory belongs to player
    bool ownsSource = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->source;});
    bool ownsTarget = any_of(playerTerritories.begin(), playerTerritories.end(), [this](Territory *t){return t == this->target;});
    bool enoughArmies = (*source->armyAmount) >= numToMove;
    return ownsSource && ownsTarget && enoughArmies;
}

//execute order
void Airlift::execute(){
    if(validate()){
        (*source->armyAmount) -= numToMove;
        (*target->armyAmount) += numToMove;
    }
    
}

// TODO
//Airlift assignment operator
Airlift& Airlift::operator=(const Airlift& ai){
	Airlift::operator=(ai);
	return *this;
}

//Airlift output stream
std::ostream& operator<<(std::ostream &strm, const Airlift &Airlift){
    return strm << "Airlift order of " << Airlift.numToMove <<  " armies from territory "
     << *Airlift.source << " to " << *Airlift.target << endl;
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
Negotiate::Negotiate(){
    type = "Negotiate";
    valid = true;
}

//Negotiate destructor
Negotiate::~Negotiate(){

}

//Negotiate copy constructor
Negotiate::Negotiate(const Negotiate& n1){
    this->type = n1.type;
    this->effect = n1.effect;
}

//Negotiate assignment operator
Negotiate& Negotiate::operator=(const Negotiate& n){
	Negotiate::operator=(n);
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
bool Negotiate::validate(){
    if (valid){
        cout << "Negotiate is valid" << endl << endl;
        return true;
    }
    else{
        cout << "ERROR: Negotiate is not valid" << endl;
        return false;
    }
}

//execute order
void Negotiate::execute(){
    //validate the order then execute
    if(validate()){
        this->hasExecuted = true;
        effect = "executed";
        cout << "Negotiate is executing" << endl;
    }
    else{
        this->hasExecuted = false;
        cout << "ERROR: Negotiate cannot be executed" << endl;
    }
}

//getter for valid
bool Negotiate::getValid(){
    return this->valid;
}

//setter for valid
void Negotiate::setValid(bool valid){
    this->valid = valid;
}

//clone method
Order* Negotiate::clone(){
    return new Negotiate(*this);
}

