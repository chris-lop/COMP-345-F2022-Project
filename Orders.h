#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <list>

//Driver function
void testOrdersLists();

//Class forward declations
class OrdersList;
class Order;
class Deploy;
class Advance;
class Bomb;
class Blockade;
class Airlift;
class Negotiate;


//Class definition
class OrdersList{
public:
    //default constructor
    OrdersList();

    //destructor
    ~OrdersList();

    //constructor with parameters
    OrdersList(std::list<Order*> order);

    //copy constructor
    OrdersList(const OrdersList& o1);

    void set_order(std::list<Order*> order);
    list<Order*>& get_order();
    void addOrder(Order* order);
    void remove(Order* order);
    void move();
private:
    std::list<Order*> order;

};

class Order{
public:
    Order();

    ~Order();

    Order(std::string description, string effect);

    Order(const Order& o1);

    // Stream insertion operator friend
    friend std::ostream& operator<<(std::ostream&, const Order&);
    std::string description;
    std::string effect;
    bool hasExecuted = false;
    

};

class Deploy : public Order{
public:
    Deploy();
    ~Deploy();
    Deploy(const Deploy& d1);
    bool validate();
    void execute();
private:
    bool valid = true;
};

class Advance : public Order{
public:
    Advance();
    ~Advance();
    Advance(const Advance& ad1);
    bool validate();
    void execute();
private:
    bool valid = true;
};

class Bomb : public Order{
public:
    Bomb();
    ~Bomb();
    Bomb(const Bomb& b1);
    bool validate();
    void execute();
private:
    bool valid = true;
};

class Blockade : public Order{
public:
    Blockade();
    ~Blockade();
    Blockade(const Blockade& bl1);
    bool validate();
    void execute();
private:
    bool valid = true;
};

class Airlift : public Order{
public:
    Airlift();
    ~Airlift();
    Airlift(const Advance& ai1);
    bool validate();
    void execute();
private:
    bool valid = true;
};

class Negotiate : public Order{
public:
    Negotiate();
    ~Negotiate();
    Negotiate(const Negotiate& n1);
    bool validate();
    void execute();
private:
    bool valid = true;
};
