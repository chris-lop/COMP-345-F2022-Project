#include <iostream> 
#include <algorithm>
#include <cmath>
#include "Player.h"
#include "Map.h"
#include "Cards.h"

/*
* Temporary Territoryt class
*/
//constructors 
// Territoryt::Territoryt() {
//     this->t = 0;
//     int arr[] = { 0,0 };
//     set_adj(arr);
// }

// //paramatrized constructor
// Territoryt::Territoryt(int t, int arr[2]){
//     this->t = t;
//     this->set_adj(arr);
// }

// //copy constructor
// Territoryt:: Territoryt (const Territoryt& t1){
//     this->t = int(t1.t);
//     std::vector<int> adjt;
//     for (int i: t1.adj){
//         adjt.push_back(i);
//     }
//     this->adj = adjt;
// }

// //setters
// void Territoryt::set_t(int t) {
//     this->t = t;
// }
// void Territoryt::set_adj(int arr[]){
//     for (int i = 0; i <2; i++){
//         this->adj.push_back(arr[i]);
//     }
// }

// //getter
// int Territoryt::get_t() {
//     return t;
// }
// std::vector<int> Territoryt::get_adj() {
//     return this->adj;
// }

/*
* Temporary Order class
*/
//constructor
Ordert::Ordert() {
    set_type("null");
}
Ordert::Ordert(std::string type) {
    this->type = type;
}

//copy constructor
Ordert::Ordert (const Ordert& o1){
    this->type = std::string(o1.type);
}

//setter
void Ordert::set_type(std::string type) {
    this->type = type;
}

//getter
std::string Ordert::get_type() {
    return this->type;
}


/*
* Player class
*/
//Default constructor
Player::Player() {
    this->name = "Null";
    this->trt = {};
    this->h = {};
    this->olst = {};
    this->army_unit = 0;
}
//Constructor with name parameter
Player::Player(std::string name){
    this->name = name;
    this->trt={};
    this->h ={};
    this->olst = {};
    this->army_unit = 0;
}
//Constructor without reinforcement pool
Player::Player(std::string name, std::vector<Territory*> trt, Hand* h, std::vector <Ordert*> olst) {
    this->name = name;
    this->trt = trt;
    this->h = h;
    this->olst = olst;
    this->army_unit = 0;
}
//Constructor with all parameters
Player::Player(std::string name, std::vector<Territory*> trt, Hand* h, std::vector <Ordert*> olst, int army_unit){
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
    for (Ordert* o: olst) {
        delete(o);
    }
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

    //copy the order vector
    std::vector<Ordert*> ot;
    for(Ordert* o: p1.olst){
        Ordert* o1 = new Ordert(o->get_type());
        ot.push_back(o1);
    }
    this->olst = ot;
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
std::vector <Ordert*> Player::get_olst() {
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
//Setter for olist
void Player::set_Ordert(std::vector <Ordert*> newolst){
    this->olst = newolst;
}
//Setter for hand
void Player::set_Player_Hand(Hand* h){
    this->h = h;
}
//Setter for army_unit
void Player::set_armyUnit(int army_unit){
    this->army_unit = army_unit;
}

//Player stream operators
std::ostream& operator << (std::ostream& strm, const Player& p){
    strm << "This player is: " << p.name << std::endl;
    strm <<"The list of territory owned: "<<std::endl;
    // for (int i = 0; i < p.trt.size(); i++) {
    //     strm << p.trt.at(i)->get_t() << "\t" ;
    // } 
    for (Territory* t: p.trt){
        strm<<t;
    }
    strm << std::endl;
    strm << "The number of army units owned: "<< p.army_unit <<std::endl;
    strm << "Player's current list of orders: ";
    for (int i = 0; i < p.olst.size(); i++) {
        std::cout << p.olst.at(i)->get_type() << "\t";
    }
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
            
            // //not sure if find() function will work, so another version of the method comparing only the names
            // for(Territory* t_owned: this->trt){
            //     if(t_owned->getTerritoryName() == t_adj->getTerritoryName()){
            //         continue;
            //     }
            //     //if the adjacent territory is not owned by the player
            //     else{
            //         //if the territory to defend was already added, skip
            //         for(Territory* t_result: result_defend){
            //             if (t_result->getTerritoryName() == t_owned->getTerritoryName()){
            //                 continue;
            //             }
            //             //if not, add to the result vector
            //             else{
            //                 result_defend.push_back(t_owned);
            //                 break;
            //             }
            //         }  
            //     }
            // }
            
            
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
        //traverse the list of adjacent territories for each t 
        for(Territory* t_adj: t->getAdjTerritories()){

            for(Territory* t_owned: this->trt){
                //the adjacent territory is owned by the player, so the player cannot attack
                if(t_adj->getTerritoryName() == t_owned->getTerritoryName()){
                    continue;
                }
                //the adjacent territory is not owned by the player, so the player can attack
                else{
                    result_attack.push_back(t_adj);
                    break;
                }
            }

        }
    }

    return result_attack;
}

//issueOrder()
//add a new order input by user to the existing list
void Player::issueOrder() {
    std::cout << "The player " << this->get_name() << "'s current list of order is: ";
    for (int i = 0; i < this->get_olst().size(); i++) {
        std::cout << this->get_olst().at(i)->get_type() << "\t";
    }
    std::cout<<std::endl;

    //prompt user to input order
    std::string order1;
    std::cout <<"Enter order to be added: " ;
    std::cin >> order1;
    std::cout << std::endl;

    //adding the input order to the existing list and return the new list
    Ordert * o1 = new Ordert(order1);
    std::vector <Ordert*> newolst;
    for (int i=0; i <this->get_olst().size(); i++){
        newolst.push_back(this->get_olst().at(i));
    }
    newolst.push_back(o1);

    this->set_Ordert(newolst);

    std::cout << "The new list of order is: ";
        for (int i = 0; i < this->get_olst().size(); i++) {
        std::cout << this->get_olst().at(i)->get_type() << "\t";
    }
}
