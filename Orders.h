#pragma once

#include <iostream>
#include <vector>

//Class forward declations
class OrdersList;
class Order;
class Deploy;
class Advance;
class Bomb;
class Blockade;
class Airlift;
class Negotiate;

//Driver function
void testOrdersLists();


//Class definition
class OrdersList{
public:
    //default constructor
    OrdersList();

    //destructor
    ~OrdersList();

    //constructor with parameters
    OrdersList(std::vector<Order*> orderList);

    //copy constructor
    OrdersList(const OrdersList& o1);

    OrdersList& operator=(const OrdersList& ol);

    void setOrder(std::vector<Order*> orderList);
    std::vector<Order*>& getOrder();
    void addOrder(Order* order);
    void remove(Order* order);
    void move(Order* order, int index);
    int getIndex(Order* order);
    friend std::ostream& operator<<(std::ostream&, const OrdersList&);


private:
    std::vector<Order*> orderList;

};

class Order{
public:
    Order();

    Order(std::string type);

    ~Order();

    Order(std::string description, std::string effect);

    Order(const Order& o1);

    Order& operator=(const Order& o);

    
    std::string getType();
    void setType(std::string description);
    std::string getEffect();
    void setEffect(std::string effect);
    bool getHasExecuted();
    void setHasExecuted(bool hasExecuted);

    // Stream insertion operator friend
    friend std::istream& operator >> (std::istream& in, Order&);
    friend std::ostream& operator << (std::ostream&, const Order&);
protected:
    std::string type;
    std::string effect;
    bool hasExecuted;
    

};

class Deploy : public Order{
public:
    Deploy();
    ~Deploy();
    Deploy(const Deploy& d1);
    Deploy& operator=(const Deploy& d1);
    friend std::ostream& operator<<(std::ostream&, const Deploy&);
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
    Advance& operator=(const Advance& ad);
    friend std::ostream& operator<<(std::ostream&, const Advance&);
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
    Bomb& operator=(const Bomb& b);
    friend std::ostream& operator<<(std::ostream&, const Bomb&);
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
    Blockade& operator=(const Blockade& bl);
    friend std::ostream& operator<<(std::ostream&, const Blockade&);
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
    Airlift& operator=(const Airlift& b);
    friend std::ostream& operator<<(std::ostream&, const Airlift&);
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
    Negotiate& operator=(const Negotiate& b);
    friend std::ostream& operator<<(std::ostream&, const Negotiate&);
    bool validate();
    void execute();
    bool getValid();
    void setValid(bool valid);
private:
    bool valid;
};
