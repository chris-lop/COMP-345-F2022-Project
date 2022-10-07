#include <iostream> 
#include <algorithm>
#include "Orders.h"

using std::cout; 
using std::string; 
using std::vector;

//OrdersList class

OrdersList::OrdersList(){
    std::vector<Order *> orderList;
    this->orderList = orderList;
}

OrdersList::OrdersList(std::vector<Order*> orderList){
    this->orderList = orderList;
}

OrdersList::OrdersList(const OrdersList& ol1){
    this->orderList = ol1.orderList;
}

OrdersList::~OrdersList(){
    for (int i = 0; i < this->orderList.size(); i++)
	{
		delete this->orderList.at(i);
	}
}

OrdersList& OrdersList::operator=(const OrdersList& ol) {
	this->orderList = ol.orderList;
	return *this;
}

void OrdersList::setOrder(std::vector<Order*> order){
    this->orderList = order;
}

std::vector<Order*>& OrdersList::getOrder(){
    return this->orderList;
}

void OrdersList::addOrder(Order* order){
    this->orderList.push_back(order);
}

void OrdersList::remove(Order* order){
    std::vector<Order*>::iterator x;
    x = find(orderList.begin(), orderList.end(), order);
    int x1 = distance(orderList.begin(), x);
    int* i = &x1;
    
    if(*i >= 0 || *i < orderList.size()){
        this->orderList.erase(orderList.begin() + *i);
     }
    else{
        cout << "ERROR: Index out of bounds";
        return;
    }
}


void OrdersList::move(Order* order, int* index){
    std::vector<Order*>::iterator x;
    x = find(orderList.begin(), orderList.end(), order);
    int x1 = distance(orderList.begin(), x);
    int* i = &x1;

    if(*i >= 0 || *i < orderList.size() || *index >= 0 || *index < orderList.size()){
        Order* tempOrder = orderList.at(*i);
        orderList.erase(orderList.begin() + *i);
        orderList.insert(orderList.begin() + *index, tempOrder);
    }
    else{
        cout << "ERROR: Index out of bounds";
        return;
    }
}

int OrdersList::getIndex(Order * order){
    std::vector<Order*>::iterator x;
    x = find(orderList.begin(), orderList.end(), order);
    return distance(orderList.begin(), x);
}

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
Order::Order(){
    type = "";
    effect = "";
    hasExecuted = false;
}

Order::Order(std::string type, std::string effect){
    this->type = type;
    this ->effect = effect;
}

Order::Order(const Order& o1){
    this->type = o1.type;
    this->effect = o1.effect;
}

Order::~Order(){

}

Order& Order::operator=(const Order& o){
	this->type = o.type;
    this->effect = o.effect;
	return *this;
}

std::string Order::getType(){
    return this->type;
}

void Order::setType(std::string type){
    this->type = type;
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
        return strm << "Order(" << order.type << ")";
    }
    else{
        return strm << "Order(" << order.type << "," << order.effect << ")";
    }
}



//class Deploy

Deploy::Deploy(){
    this->type = "Deploy";
    valid = true;
}

Deploy::~Deploy(){

}

Deploy::Deploy(const Deploy& d1){
    this->type = d1.type;
    this->effect = d1.effect;
}

Deploy& Deploy::operator=(const Deploy& d1){
	Order::operator=(d1);
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Deploy &Deploy){
    if(!Deploy.hasExecuted){
        return strm << "Deploy(" << Deploy.type << ")";
    }
    else{
        return strm << "Deploy(" << Deploy.type << "," << Deploy.effect << ")";
    }
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
    type = "Advance";
    valid = true;
}

Advance::~Advance(){

}

Advance::Advance(const Advance& ad1){
    this->type = ad1.type;
    this->effect = ad1.effect;
}

Advance& Advance::operator=(const Advance& ad){
	Advance::operator=(ad);
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Advance &Advance){
    if(!Advance.hasExecuted){
        return strm << "Advance(" << Advance.type << ")";
    }
    else{
        return strm << "Advance(" << Advance.type << "," << Advance.effect << ")";
    }
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
    type = "Bomb";
    valid = true;
}

Bomb::~Bomb(){

}

Bomb::Bomb(const Bomb& b1){
    this->type = b1.type;
    this->effect = b1.effect;
}

Bomb& Bomb::operator=(const Bomb& b){
	Bomb::operator=(b);
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Bomb &Bomb){
    if(!Bomb.hasExecuted){
        return strm << "Bomb(" << Bomb.type << ")";
    }
    else{
        return strm << "Bomb(" << Bomb.type << "," << Bomb.effect << ")";
    }
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
    type = "Blockade";
    valid = true;
}

Blockade::~Blockade(){

}

Blockade::Blockade(const Blockade& bl1){
    this->type = bl1.type;
    this->effect = bl1.effect;
}

Blockade& Blockade::operator=(const Blockade& bl){
	Blockade::operator=(bl);
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Blockade &Blockade){
    if(!Blockade.hasExecuted){
        return strm << "Blockade(" << Blockade.type << ")";
    }
    else{
        return strm << "Blockade(" << Blockade.type << "," << Blockade.effect << ")";
    }
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
    type = "Airlift";
    valid = true;
}

Airlift::~Airlift(){

}

Airlift::Airlift(const Airlift& ai1){
    this->type = ai1.type;
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

Airlift& Airlift::operator=(const Airlift& ai){
	Airlift::operator=(ai);
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Airlift &Airlift){
    if(!Airlift.hasExecuted){
        return strm << "Airlift(" << Airlift.type << ")";
    }
    else{
        return strm << "Airlift(" << Airlift.type << "," << Airlift.effect << ")";
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
    type = "Negotiate";
    valid = true;
}

Negotiate::~Negotiate(){

}

Negotiate::Negotiate(const Negotiate& n1){
    this->type = n1.type;
    this->effect = n1.effect;
}

Negotiate& Negotiate::operator=(const Negotiate& n){
	Negotiate::operator=(n);
	return *this;
}

std::ostream& operator<<(std::ostream &strm, const Negotiate &Negotiate){
    if(!Negotiate.hasExecuted){
        return strm << "Negotiate(" << Negotiate.type << ")";
    }
    else{
        return strm << "Negotiate(" << Negotiate.type << "," << Negotiate.effect << ")";
    }
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

