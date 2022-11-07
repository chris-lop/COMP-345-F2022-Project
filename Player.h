#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
class OrdersList;
class Territory;
class Hand;

class Player {
private:
    //player name
    std::string name;
    //list of territories owned by the player
    std::vector <Territory*> trt;
    //hand of cards owned by the player
    Hand* h;
    //list of orders by the player
    OrdersList* olst;
    //number of army units owned
    int army_unit;
    // List of players this player has a negotiation with
    // (and cannot attack for the remainder of the turn)
    // Reset when army units added to the reinforcement
    // pool, at the start of the turn
    vector<Player*> negotiatedPlayers;

public:
    //default constructor
    Player();
    //destructor
    ~Player();

    //constructor with name parameter only
    Player(std::string name);
    //constructor without reinforcement pool
    Player(std::string name, std::vector<Territory*> trt, Hand* h, OrdersList* olst);
    //constructor with all parameters
    Player(std::string name, std::vector<Territory*> trt, Hand* h, OrdersList* olst, int army_unit);
    //copy constructor
    Player (const Player& p1);

    //stream insertion operator
    friend std::ostream& operator << (std::ostream& strm, const Player& p);
    friend std::istream& operator >> (std::istream& in, Player& p);

    //getter functions
    std::string get_name();
    std::vector <Territory*> get_trt();
    OrdersList* get_olst();
    Hand* get_Phand();
    int get_armyUnit();

    //setter functions
    void set_Pname(std::string name);
    void set_Trt(std::vector<Territory*>trt);
    void set_Olst(OrdersList* olst);
    void set_Player_Hand(Hand* h);
    void set_armyUnit(int army_unit);
    
    //methods to implement for assignment 1
    //issue a list of territories to be defended by the player based on the player owned territories
    std::vector <Territory*> toDefend();
    //issue a list of territories that can be attacked by the player based on the player owned territories
    std::vector <Territory*> toAttack();
    //add a new order input by user to the existing list
    void issueOrder();

    // Other methods
    // Adds player to the list of negotiated players
    void addNegotiatedPlayer(Player *p);
};//end class Player

//free function testPlayer
// void testPlayer();


#endif
