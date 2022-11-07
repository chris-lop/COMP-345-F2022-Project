#include <iostream> 
#include <algorithm>
#include <cmath>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"

using std::vector;

/*
* Player class
*/
//Default constructor
Player::Player() {
    this->name = "Null";
    this->trt = {};
    this->h = new Hand();
    this->olst = new OrdersList();
    this->army_unit = 0;
}
//Constructor with name parameter
Player::Player(std::string name){
    this->name = name;
    this->trt={};
    this->h = new Hand();
    // this->olst = new OrdersList();
    this->army_unit = 0;
}
//Constructor without reinforcement pool

Player::Player(std::string name, std::vector<Territory*> trt, Hand* h, OrdersList* olst) {
    this->name = name;
    this->trt = trt;
    this->h = h;
    // this->olst = olst;
    this->army_unit = 0;
}
//Constructor with all parameters 
Player::Player(std::string name, std::vector<Territory*> trt, Hand* h, OrdersList* olst, int army_unit){
    this->name = name;
    this->trt = trt;
    this->h = h;
    this->olst = olst;
    this->army_unit = army_unit;
}

//Destructor
Player::~Player() {
    for (Territory* t: trt) {
        delete(t);
    }
    delete h;
    // delete olst;
}

//Copy constructor
Player :: Player(const Player& p1){
    this->name = std::string(p1.name);

    //copy the territory vector
    for (Territory t: p1.trt){
        Territory* t1 = new Territory(t);
        this->trt.push_back(t1);
    }

    this->h = new Hand(*p1.h);
    this->olst = new OrdersList(*p1.olst);
}

//Getter for name
std::string Player::get_name() {
        return this->name;
}
//Getter for trt
std::vector <Territory*> Player::get_trt() {
        return this->trt;
}   
//Getter for olst
OrdersList* Player::get_olst() {
        return this->olst;
}
//Getter for hand
Hand* Player::get_Phand(){
    return this->h;
}
//Getter for army_unit
int Player::get_armyUnit(){
    return this->army_unit;
}

//Setter for name
void Player::set_Pname(std::string name){
    this->name = name;
}
//Setter for territory list
void Player::set_Trt(std::vector<Territory*> trt){
    this->trt = trt;
}
//Setter for order list
void Player::set_Olst(OrdersList* newolst){
    this->olst = newolst;
}
//Setter for hand
void Player::set_Player_Hand(Hand* h){
    this->h = h;
}
//Setter for army_unit
// ALSO: clears the list of negotiated players,
// since it's the start of a turn
void Player::set_armyUnit(int army_unit){
    this->army_unit = army_unit;
    if (army_unit > this->army_unit) {
        negotiatedPlayers.clear();
    }
}

void Player::addNegotiatedPlayer(Player *p) {
    negotiatedPlayers.push_back(p);
}

//Player stream operators
std::ostream& operator << (std::ostream& strm, const Player& p){
    strm << "This player is: " << p.name << std::endl;
    strm <<"The list of territory owned: "<<std::endl;

    for (Territory* t: p.trt){
        string t_name = *(t->getTerritoryName());
        strm<< t_name<<"\t";
    }
    strm << "\n";
    strm << "The number of army units owned: "<< p.army_unit <<std::endl;
    strm << "Player's current list of orders: ";
    // strm << p.olst;
    strm << std::endl;
    return strm;
}
std::istream& operator >> (std::istream& in, Player& p){
    std::cout << "Enter player name: ";
    in >> p.name;
    return in;
}

//method corrected from assignment 1
//toDefend() 
//issue a list of territories to be defended by the player based on the player owned territories
std::vector <Territory*> Player::toDefend() {
    
    //new vector of Territory to be returned as result
    std::vector <Territory*> result_defend; 

    for (Territory* t : this->trt){
        
        //traverse the list of adjacent territories for each t 
        for(Territory* t_adj: t->getAdjTerritories()){
            //verify if each territory in the adjacent territories list is in the list of territories owned
            
            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end()){
                //The adjacent territory was found in the list of owned territories
                //We don't need to defend the territory t
                continue;
            }

            //The adjacent territory was not found, thus, the territory t must be defended
            else{
                //if the territory to defend was already added, skip
                if((std::find(result_defend.begin(),result_defend.end(), t)) != result_defend.end()){
                    continue;
                }
                //if not, add to the result vector
                else{result_defend.push_back(t);}
            }
        }
    }
    return result_defend; 
}

//toAttack()
//issue a list of territories that can be attacked by the player based on the player owned territories
std::vector <Territory*> Player::toAttack(){
    //vector territory to be returned as result
    std::vector <Territory*> result_attack;
 
    for (Territory* t : this->trt){
        //traverse the list of adjacent territories for each territory t
        for(Territory* t_adj: t->getAdjTerritories()){

            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end()){
                //The adjacent territory was found in the list of owned territories
                //We don't need to attack the territory t
                continue;
            }

            //The adjacent territory was not found in owned territories, thus, the territory t_adj can be attacked
            else{
                //if the territory to attack was already added, skip
                if((std::find(result_attack.begin(),result_attack.end(), t_adj)) != result_attack.end()){
                    continue;
                }
                //if not, add to the result vector
                else{result_attack.push_back(t_adj);}
            }

        }
    }

    return result_attack;
}

//issueOrder()
//add a new order input by user to the existing list
void Player::issueOrder() {
    std::cout << "The player " << this->get_name() << "'s current list of order is: ";
    std::cout<< *(this->get_olst());
    std::cout<<std::endl;

    //prompt user to input order
    std::string order1;
    std::cout <<"Enter order to be added: " ;
    std::cin >> order1;
    std::cout << std::endl;

    //adding the input order to the existing list and return the new list
    // Order *o1 = new Order(order1);
    // this->get_olst()->addOrder(o1);
    // std::cout << "The new list of order is: ";
    // std::cout << *(this->get_olst()) << std::endl;

}
