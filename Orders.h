#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>

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
    OrdersList(std::vector<Order*> order);

    //copy constructor
    OrdersList(const OrdersList& o1);

    void set_order(std::vector<Order*> order);
    std::vector<Order*>& get_order();
    void addOrder(Order* order);
    void remove(int* i);
    void move(int* init, int* final);
private:
    std::vector<Order*> order;

};

class Order{
public:
    Order();

    ~Order();

    Order(std::string description, std::string effect);

    Order(const Order& o1);
    
    std::string getDescription();
    void setDescription(std::string description);
    std::string getEffect();
    void setEffect(std::string effect);
    bool getHasExecuted();
    void setHasExecuted(bool hasExecuted);

    // Stream insertion operator friend
    friend std::ostream& operator<<(std::ostream&, const Order&);
protected:
    std::string description;
    std::string effect;
    bool hasExecuted;
    

};

class Deploy : public Order{
public:
    Deploy();
    ~Deploy();
    Deploy(const Deploy& d1);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid;
};

class Advance : public Order{
public:
    Advance();
    ~Advance();
    Advance(const Advance& ad1);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid;
};

class Bomb : public Order{
public:
    Bomb();
    ~Bomb();
    Bomb(const Bomb& b1);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid;
};

class Blockade : public Order{
public:
    Blockade();
    ~Blockade();
    Blockade(const Blockade& bl1);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid ;
};

class Airlift : public Order{
public:
    Airlift();
    ~Airlift();
    Airlift(const Airlift& ai1);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid;
};

class Negotiate : public Order{
public:
    Negotiate();
    ~Negotiate();
    Negotiate(const Negotiate& n1);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid;
};
