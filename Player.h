#pragma once

#include <vector>
#include <string>
class Territory;
class Hand;
#ifndef PLAYER_H
#define PLAYER_H


/*
* Temporary Order class
*/
class Ordert {
private:
    //Order type
    std::string type;

public:
    //default constructor
    Ordert();
    //constructor with parameter
    Ordert(std::string type);
    //copy constructor
    Ordert (const Ordert& o1);
    //setter
    void set_type(std::string type);
    //getter
    std::string get_type();
};//end class Order 


class Player {
private:
    //player name
    std::string name;
    //list of territories owned by the player
    std::vector <Territory*> trt;
    //hand of cards owned by the player
    Hand* h;
    //list of orders by the player
    std::vector <Ordert*> olst;
    //number of army units owned
    int army_unit;

public:
    //default constructor
    Player();
    //destructor
    ~Player();

    //constructor with all parameters
    Player(std::string name, std::vector<Territory*> trt, Hand* h, std::vector <Ordert*> olst);
    //constructor with name parameter only
    Player(std::string name);
    //copy constructor
    Player (const Player& p1);

    //stream insertion operator
    friend std::ostream& operator << (std::ostream& strm, const Player& p);
    friend std::istream& operator >> (std::istream& in, Player& p);

    //getter functions
    std::string get_name();
    std::vector <Territory*> get_trt();
    std::vector <Ordert*> get_olst();
    Hand* get_Phand();
    int get_armyUnit();

    //setter functions
    void set_Pname(std::string name);
    void set_Trt(std::vector<Territory*>trt);
    void set_Ordert(std::vector <Ordert*> olst);
    void set_Player_Hand(Hand* h);
    void set_armyUnit(int army_unit);
    
    //methods to implement for assignment 1
    //issue a list of territories to be defended by the player based on the player owned territories
    std::vector <Territory*> toDefend();
    //issue a list of territories that can be attacked by the player based on the player owned territories
    std::vector <Territory*> toAttack();
    //add a new order input by user to the existing list
    void issueOrder();
};//end class Player

//free function testPlayer
// void testPlayer();


#endif
