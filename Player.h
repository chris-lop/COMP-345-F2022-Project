#include <vector>
#include <string>

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

    void set_t(int t);
    void set_adj(int arr[]);
    int get_t();
    std::vector <int> get_adj();
}; //end Territoryt

/*
* Temporary Card class
*/
class Cardt {
private:
    std::string ctype;

public:
    Cardt();
    Cardt(std::string ctype);
    void set_ctype(std::string ctype);
    std::string get_ctype();
}; //end Cardt

/*
* Temporary Order class
*/
class Ordert {
private:
    std::string type;

public:
    Ordert();
    Ordert(std::string type);

    void set_type(std::string type);
    std::string get_type();
};//end class Order 


class Player {
private:
    std::string name;
    std::vector <Territoryt*> trt;
    std::vector<Cardt*> hand;
    std::vector <Ordert*> olst;

public:
    //default constructor
    Player();
    //destructor
    ~Player();

    //constructor with parameter
    Player(std::string name, std::vector<Territoryt*> trt, std::vector<Cardt*> hand, std::vector <Ordert*> olst);
    //copy constructor
    Player (const Player& p1);

    //stream insertion operator
    friend std::ostream& operator << (std::ostream& strm, const Player& p);
    friend std::istream& operator >> (std::istream& in, Player& p);

    //getter functions
    std::string get_name();
    std::vector <Territoryt*> get_trt();
    std::vector <Ordert*> get_olst();
    
    //setter functions
    void set_Order(std::vector <Ordert*> olst);
    
    void toDefend();
    void toAttack();
    void issueOrder();
};//end class Player

//free function testPlayer
void testPlayer();


#endif
