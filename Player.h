#include <vector>
#include <string>
class Hand;
#ifndef PLAYER_H
#define PLAYER_H


/*
* Temporary Territory class
* An int represents a territory, and an array of int represents its adjacent territories.
* A 0 value territory is an empty territory.
*/
class Territoryt {

private:
    int t;
    std::vector <int> adj;

public:
    Territoryt();
    Territoryt(int t, int arr[]);
    Territoryt (const Territoryt& t1);

    void set_t(int t);
    void set_adj(int arr[]);
    int get_t();
    std::vector<int> get_adj();
}; //end Territoryt

/*
* Temporary Order class
*/
class Ordert {
private:
    std::string type;

public:
    Ordert();
    Ordert(std::string type);
    Ordert (const Ordert& o1);

    void set_type(std::string type);
    std::string get_type();
};//end class Order 


class Player {
private:
    std::string name;
    std::vector <Territoryt*> trt;
    Hand* h;
    std::vector <Ordert*> olst;

public:
    //default constructor
    Player();
    //destructor
    ~Player();

    //constructor with all parameters
    Player(std::string name, std::vector<Territoryt*> trt, Hand* h, std::vector <Ordert*> olst);
    //constructor with name parameter only
    Player(std::string name);
    //copy constructor
    Player (const Player& p1);

    //stream insertion operator
    friend std::ostream& operator << (std::ostream& strm, const Player& p);
    friend std::istream& operator >> (std::istream& in, Player& p);

    //getter functions
    std::string get_name();
    std::vector <Territoryt*> get_trt();
    std::vector <Ordert*> get_olst();
    Hand* get_Phand();

    //setter functions
    void set_Pname(std::string name);
    void set_Ordert(std::vector <Ordert*> olst);
    void set_Player_Hand(Hand* h);
    
    void toDefend();
    void toAttack();
    void issueOrder();
};//end class Player

//free function testPlayer
void testPlayer();


#endif
