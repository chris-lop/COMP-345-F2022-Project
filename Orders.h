#pragma once

#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"

//Class forward declations
class OrdersList;
class Order;
class Deploy;
class Advance;
class Bomb;
class Blockade;
class Airlift;
class Negotiate;

//Driver functions
void testOrdersLists();
void testOrderExecution();

//OrdersList lass definition
class OrdersList{
public:
    //OrdersList default constructor
    OrdersList();
    //OrdersList destructor
    ~OrdersList();
    //OrdersList paramatrized constructor
    OrdersList(std::vector<Order*> orderList);
    //OrdersList copy constructor
    OrdersList(const OrdersList& o1);
    //OrdersList assignment operator 
    OrdersList& operator=(const OrdersList& ol);
    //Setter method for OrdersList 
    void setOrder(std::vector<Order*> orderList);
    //Getter method for OrdersList
    std::vector<Order*>& getOrder();
    //Add an order to the Order list
    void addOrder(Order* order);
    //Remove an order from the Order list
    void remove(Order* order);
    //Move an Order to position "index" in the Order list
    void move(Order* order, int index);
    //Get the index of a given order
    int getIndex(Order* order);
    //Output stream
    friend std::ostream& operator<<(std::ostream&, const OrdersList&);


private:
    //orderList is the list of vector type that stores all the orders
    std::vector<Order*> orderList;

};

//Order lass definition
class Order{
public:
    //Order default constructor
    Order();
    //Order paramatrized constructor
    Order(std::string type);
    //Order destructor
    ~Order();
    //Order paramatrized constructor
    Order(std::string type, std::string effect);
    //Order copy constructor
    Order(const Order& o1);
    //Order assignment operator
    Order& operator=(const Order& o);
    //Getter for type
    std::string getType();
    //Setter for type
    void setType(std::string description);
    //Getter for effect
    std::string getEffect();
    //setter for effect
    void setEffect(std::string effect);
    //getter for hasExecuted
    bool getHasExecuted();
    //Setter for hasExecuted
    void setHasExecuted(bool hasExecuted);
     //Order input stream
    friend std::istream& operator >> (std::istream& in, Order&);
    //Order output stream
    friend std::ostream& operator << (std::ostream&, const Order&);
    // Pure virtual execute() method
    virtual void execute() = 0;
    // Pure virtual clone method, required for the copy constructor
    virtual Order* clone() = 0;
protected:
    //type is the order type (deploy, advance, bomb, airlift, negotiate, blockade)
    std::string type;
    //effect is the effect the execution had on the order
    std::string effect;
    //hasExecuted checks if the order has executed yet
    bool hasExecuted;
};

//Deploy lass definition
class Deploy : public Order{
public:
    //Default ctor
    Deploy();
    //Deploy constructor
    Deploy(Territory *target, Player *player, int numberUnits);
    //Deploy destructor
    ~Deploy();
    //Deploy copy constructor
    Deploy(const Deploy& d1);
    //Deploy assignment operator
    Deploy& operator=(const Deploy& d1);
    //Deploy output stream
    friend std::ostream& operator<<(std::ostream&, const Deploy&);
    //Validate if the order is valid
    bool validate();
    //execute order
    void execute();
    // Clone method, required for the copy constructor
    virtual Order* clone();
private:
    Territory *target;
    Player *player;
    int numberUnits;
};

//Advance lass definition
class Advance : public Order{
public:
    //Advance default constructor
    Advance();
    //Advance constructor
    Advance(Territory *source, Territory *target, Player *player, int numberUnits);
    //Advance destructor
    ~Advance();
    //Advance copy constructor
    Advance(const Advance& ad1);
    //Advance assignment operator
    Advance& operator=(const Advance& ad);
    //Advance output stream
    friend std::ostream& operator<<(std::ostream&, const Advance&);
    //Validate if the order is valid
    bool validate();
    //execute order
    void execute();
    // Clone method, required for the copy constructor
    virtual Order* clone();
private:
    //valid stores the information if the order is valid
    Territory *source;
    Territory *target;
    Player *player;
    int numberUnits;
};

//Bomb lass definition
class Bomb : public Order{
public:
    //Bomb default constructor
    Bomb();
    //Bomb destructor
    ~Bomb();
    //Bomb copy constructor
    Bomb(const Bomb& b1);
    //Bomb assignment operator
    Bomb& operator=(const Bomb& b);
    //Bomb output stream
    friend std::ostream& operator<<(std::ostream&, const Bomb&);
    //Validate if the order is valid
    bool validate();
    //execute order
    void execute();
    //getter for valid
    bool getValid();
    //setter for valid
    void setValid(bool valid);
    // Clone method, required for the copy constructor
    virtual Order* clone();
private:
    //valid stores the information if the order is valid
    bool valid;
};

//Blockade lass definition
class Blockade : public Order{
public:
    //Blockade default constructor
    Blockade();
    //Blockade destructor
    ~Blockade();
    //Blockade copy constructor
    Blockade(const Blockade& bl1);
    //Blockade assignment operator
    Blockade& operator=(const Blockade& bl);
    //Blockade output stream
    friend std::ostream& operator<<(std::ostream&, const Blockade&);
    //Validate if the order is valid
    bool validate();
    //execute order
    void execute();
    //getter for valid
    bool getValid();
    //setter for valid
    void setValid(bool valid);
    // Clone method, required for the copy constructor
    virtual Order* clone();
private:
    //valid stores the information if the order is valid
    bool valid;
};

//Airlift lass definition
class Airlift : public Order{
public:
    //Airlift default constructor
    Airlift();
    //Airlift Paramaterized constructor
    Airlift(Territory *source, Territory *target, Player *player, int numToMove);
    //Airlift destructor
    ~Airlift();
    //Airlift copy constructor
    Airlift(const Airlift& ai1);
    //Airlift assignment operator
    Airlift& operator=(const Airlift& b);
    //Airlift output stream
    friend std::ostream& operator<<(std::ostream&, const Airlift&);
    //Validate if the order is valid
    bool validate();
    //execute order
    void execute();
    // Clone method, required for the copy constructor
    virtual Order* clone();
private:
    Territory *source, *target;
    Player *player;
    int numToMove;
};

//Negotiate lass definition
class Negotiate : public Order{
public:
    //Negotiate default constructor
    Negotiate();
    //Negotiate destructor
    ~Negotiate();
    //Negotiate copy constructor
    Negotiate(const Negotiate& n1);
    //Negotiate assignment operator
    Negotiate& operator=(const Negotiate& b);
    //Negotiate output stream
    friend std::ostream& operator<<(std::ostream&, const Negotiate&);
    //Validate if the order is valid
    bool validate();
    //execute order
    void execute();
    //getter for valid
    bool getValid();
    //setter for valid
    void setValid(bool valid);
    // Clone method, required for the copy constructor
    virtual Order* clone();
private:
    //valid stores the information if the order is valid
    bool valid;
};
