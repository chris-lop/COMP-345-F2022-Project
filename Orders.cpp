#include <iostream> 
#include "Orders.h"
#include <ctime>

using std::cout; 
using std::endl; 
using std::string; 
using std::vector;

//OrdersList class

OrdersList::OrdersList(){
    std::vector<Order *> order;
    this->order = order;
}

OrdersList::OrdersList(std::vector<Order*> order){
    this->order = order;
}

OrdersList::OrdersList(const OrdersList& ol1){
    this->order = ol1.order;
}

OrdersList::~OrdersList(){
    for (int i = 0; i < this->order.size(); i++)
	{
		delete this->order.at(i);
	}
}

void OrdersList::set_order(std::vector<Order*> order){
    this->order = order;
}

std::vector<Order*>& OrdersList::get_order(){
    return this->order;
}

void OrdersList::addOrder(Order* order){
    this->order.push_back(order);
}

void OrdersList::remove(int* i){
    if(*i >= 0 || *i < order.size()){
        this->order.erase(order.begin() + *i);
     }
    else{
        cout << "ERROR: Index out of bounds";
        return;
    }
}


void OrdersList::move(int* init, int* final){
    if(*init >= 0 || *init < order.size() || *final >= 0 || *final < order.size()){
        Order* tempOrder = order.at(*init);
        order.erase(order.begin() + *init);
        order.insert(order.begin() + *final, tempOrder);
    }
    else{
        cout << "ERROR: Index out of bounds";
        return;
    }
}



//Order class
Order::Order(){
    description = "";
    effect = "";
    hasExecuted = false;
}

Order::Order(std::string description, std::string effect){
    this->description = description;
    this ->effect = effect;
}

Order::Order(const Order& o1){
    this->description = o1.description;
    this->effect = o1.effect;
}

Order::~Order(){

}

std::string Order::getDescription(){
    return this->description;
}

void Order::setDescription(std::string description){
    this->description = description;
}

std::string Order::getEffect(){
    return this->effect;
}

void Order::setEffect(std::string effect){
    this->effect = effect;
}

bool Order::getHasExecuted(){
    return this->hasExecuted;
}

void Order::setHasExecuted(bool hasExecuted){
    this->hasExecuted = hasExecuted;
}

std::ostream& operator<<(std::ostream &strm, const Order &order){
    if(!order.hasExecuted){
        return strm << "Order(" << order.description << ")";
    }
    else{
        return strm << "Order(" << order.description << "," << order.effect << ")";
    }
}



//class Deploy

Deploy::Deploy(){
    this->description = "Deply";
    valid = true;
}

Deploy::~Deploy(){

}

Deploy::Deploy(const Deploy& d1){
    this->description = d1.description;
    this->effect = d1.effect;
}

bool Deploy::validate(){
    if (valid){
        cout << "This order is valid";
        return true;
    }
    else{
        cout << "ERROR: This order is not valid";
        return false;
    }
}

void Deploy::execute(){
    if(validate()){
        this->hasExecuted = true;
        cout << "Deploy is executing";
    }
}

bool Deploy::getValid(){
    return this->valid;
}

void Deploy::setValid(bool valid){
    this->valid = valid;
}

//class Advance

Advance::Advance(){
    description = "Advance";
    valid = true;
}

Advance::~Advance(){

}

Advance::Advance(const Advance& ad1){
    this->description = ad1.description;
    this->effect = ad1.effect;
}

bool Advance::validate(){
    if (valid){
        cout << "This order is valid";
        return true;
    }
    else{
        cout << "ERROR: This order is not valid";
        return false;
    }
}

void Advance::execute(){
    if(validate()){
        this->hasExecuted = true;
        cout << "Advance is executing";
    }
}

bool Advance::getValid(){
    return this->valid;
}

void Advance::setValid(bool valid){
    this->valid = valid;
}

//class Bomb

Bomb::Bomb(){
    description = "Bomb";
    valid = true;
}

Bomb::~Bomb(){

}

Bomb::Bomb(const Bomb& b1){
    this->description = b1.description;
    this->effect = b1.effect;
}

bool Bomb::validate(){
    if (valid){
        cout << "This order is valid";
        return true;
    }
    else{
        cout << "ERROR: This order is not valid";
        return false;
    }
}

void Bomb::execute(){
    if(validate()){
        this->hasExecuted = true;
        cout << "Bomb is executing";
    }
}

bool Bomb::getValid(){
    return this->valid;
}

void Bomb::setValid(bool valid){
    this->valid = valid;
}


//class Blockade

Blockade::Blockade(){
    description = "Blockade";
    valid = true;
}

Blockade::~Blockade(){

}

Blockade::Blockade(const Blockade& bl1){
    this->description = bl1.description;
    this->effect = bl1.effect;
}

bool Blockade::validate(){
    if (valid){
        cout << "This order is valid";
        return true;
    }
    else{
        cout << "ERROR: This order is not valid";
        return false;
    }
}

void Blockade::execute(){
    if(validate()){
        this->hasExecuted = true;
        cout << "Blockade is executing";
    }
}

bool Blockade::getValid(){
    return this->valid;
}

void Blockade::setValid(bool valid){
    this->valid = valid;
}

//class Airlift

Airlift::Airlift(){
    description = "Airlift";
    valid = true;
}

Airlift::~Airlift(){

}

Airlift::Airlift(const Airlift& ai1){
    this->description = ai1.description;
    this->effect = ai1.effect;
}

bool Airlift::validate(){
    if (valid){
        cout << "This order is valid";
        return true;
    }
    else{
        cout << "ERROR: This order is not valid";
        return false;
    }
}

void Airlift::execute(){
    if(validate()){
        this->hasExecuted = true;
        cout << "Airlift is executing";
    }
}

bool Airlift::getValid(){
    return this->valid;
}

void Airlift::setValid(bool valid){
    this->valid = valid;
}


//class Negotiate

Negotiate::Negotiate(){
    description = "Negotiate";
    valid = true;
}

Negotiate::~Negotiate(){

}

Negotiate::Negotiate(const Negotiate& n1){
    this->description = n1.description;
    this->effect = n1.effect;
}

bool Negotiate::validate(){
    if (valid){
        cout << "This order is valid";
        return true;
    }
    else{
        cout << "ERROR: This order is not valid";
        return false;
    }
}

void Negotiate::execute(){
    if(validate()){
        this->hasExecuted = true;
        cout << "Negotiate is executing";
    }
}

bool Negotiate::getValid(){
    return this->valid;
}

void Negotiate::setValid(bool valid){
    this->valid = valid;
}