#include <iostream> 
#include "Orders.h"
#include <iostream>
#include <list>
#include <ctime>

using std::cout; 
using std::endl; 
using std::string; 
using std::list;

//OrdersList class

OrdersList::OrdersList(){

}

OrdersList::OrdersList(std::list<Order*> order){
    set_order(order);
}

OrdersList::OrdersList(const OrdersList& ol1){
    this->order = ol1.order;
}

OrdersList::~OrdersList(){
 
}

void OrdersList::set_order(std::list<Order*> order){
    this->order = order;
}

list<Order*>& OrdersList::get_order(){
    return this->order;
}

void OrdersList::addOrder(Order* order){
    this->order.push_back(order);
}

void OrdersList::remove(Order* order){
    this->order.remove(order);
}

//------------------------
void OrdersList::move(){

}
//--------------------


//Order class
Order::Order(){
    description = "";
    effect = "";
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

//class Advance

Advance::Advance(){
    description = "Advance";
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

//class Bomb

Bomb::Bomb(){
    description = "Bomb";
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


//class Blockade

Blockade::Blockade(){
    description = "Blockade";
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

//class Airlift

Airlift::Airlift(){
    description = "Airlift";
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


//class Negotiate

Negotiate::Negotiate(){
    description = "Negotiate";
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