#include <iostream> 
#include <algorithm>
#include "Player.h"
#include "Cards.h"

/*
* Temporary Territoryt class
*/
Territoryt::Territoryt() {
    this->t = 0;
    int arr[] = { 0,0 };
    set_adj(arr);
}
Territoryt::Territoryt(int t, int arr[2]){
    this->t = t;
    this->set_adj(arr);
}

void Territoryt::set_t(int t) {
    this->t = t;
}

void Territoryt::set_adj(int arr[]){
    for (int i = 0; i <2; i++){
        this->adj.push_back(arr[i]);
    }
}

int Territoryt::get_t() {
    return t;
}

std::vector<int> Territoryt::get_adj() {
    return this->adj;
}

//copy constructor
Territoryt:: Territoryt (const Territoryt& t1){
    this->t = int(t1.t);
    std::vector<int> adjt;
    for (int i: t1.adj){
        adjt.push_back(i);
    }
    this->adj = adjt;
}


/*
* Temporary Order class
*/
Ordert::Ordert() {
    set_type("null");
}

Ordert::Ordert(std::string type) {
    this->type = type;
}

void Ordert::set_type(std::string type) {
    this->type = type;
}

std::string Ordert::get_type() {
    return this->type;
}
//copy constructor
Ordert::Ordert (const Ordert& o1){
    this->type = std::string(o1.type);
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
}
Player::~Player() {
    for (Territoryt* t: trt) {
        delete(t);
    }
    delete h;
    for (Ordert* o: olst) {
        delete(o);
    }
}
//Constructor with parameter
Player::Player(std::string name, std::vector<Territoryt*> trt, Hand* h, std::vector <Ordert*> olst) {
    this->name = name;
    this->trt = trt;
    this->h = h;
    this->olst = olst;
}
//Constructor with name parameter
Player::Player(std::string name){
    this->name = name;
    this->trt={};
    this->h ={};
    this->olst = {};
}
//Copy constructor
Player :: Player(const Player& p1){
    this->name = std::string(p1.name);

    //copy the territory vector
    std::vector<Territoryt*> vt;
    for (Territoryt* t : p1.trt){
        int arr[2];
        arr[0] = t->get_adj().at(0);
        arr[1] = t->get_adj().at(1);
        Territoryt* t1 = new Territoryt(t->get_t(), arr); 
        vt.push_back(t1);
        }
    this->trt = vt;

    this->h = new Hand(*p1.h);

    //copy the territory vector
    std::vector<Ordert*> ot;
    for(Ordert* o: p1.olst){
        Ordert* o1 = new Ordert(o->get_type());
        ot.push_back(o1);
    }
    this->olst = ot;
}

//Getter
std::string Player::get_name() {
        return this->name;
}

std::vector <Territoryt*> Player::get_trt() {
        return this->trt;
}
    
std::vector <Ordert*> Player::get_olst() {
        return this->olst;
}

Hand* Player::get_Phand(){
    return this->h;
}

//Player stream operators
std::ostream& operator << (std::ostream& strm, const Player& p){
    strm << "This player is: " << p.name << std::endl;
    strm <<"Territory owned: ";
    for (int i = 0; i < p.trt.size(); i++) {
        strm << p.trt.at(i)->get_t() << "\t" ;
    } 
    strm << std::endl;
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

//setter
void Player::set_Pname(std::string name){
    this->name = name;
}
void Player::set_Ordert(std::vector <Ordert*> newolst){
    this->olst = newolst;
}
void Player::set_Player_Hand(Hand* h){
    this->h = h;
}

//required methods for assignment 1
//toDefend() 
//issue list of territories to be defended by the player based on the player owned territories
std::vector <Territoryt*> Player::toDefend() {
    
    std::vector <Territoryt*> result_defend; 
    
    for (int i = 0; i < this->get_trt().size(); i++) {

        if (this->get_trt().at(i)->get_adj().at(0) != 0 || this->get_trt().at(i)->get_adj().at(1) != 0){
            bool found = false;
            bool found2 = false;

            for (int j =0; j < this->get_trt().size(); j++){
                int elmt = this->get_trt().at(j)->get_t();

                if(this->get_trt().at(i)->get_adj().at(0) == elmt){
                    found = true;
                    break;
                }  
            }

            for (int j =0; j < this->get_trt().size(); j++){
                int elmt = this->get_trt().at(j)->get_t();

                if(this->get_trt().at(i)->get_adj().at(1) == elmt){
                    found2 = true;
                    break;
                }  
            }

            if (found == true && found2 == true){
                continue;
            }
            else if(found == true && this->get_trt().at(i)->get_adj().at(1) == 0||found2 == true && this->get_trt().at(i)->get_adj().at(0) != 0){
                Territoryt* tempt = new Territoryt(*(this->get_trt().at(i)));
                result_defend.push_back(tempt);
                continue;
            }
            else { 
                 Territoryt* tempt2 = new Territoryt(*(this->get_trt().at(i)));
                 result_defend.push_back(tempt2);
                 continue;
            }
        }
    }
    return result_defend; 
}

//toAttack()
//issue list of territories that can be attacked by the player based on the player owned territories
std::vector <Territoryt*> Player::toAttack(){
    
    std::vector <Territoryt*> result_attack;

    for (int i = 0; i < this->get_trt().size(); i++) {

        if (this->get_trt().at(i)->get_adj().at(0) != 0 || this->get_trt().at(i)->get_adj().at(1) != 0){
            bool found = false;

            for (int j =0; j < this->get_trt().size(); j++){
                int elmt = this->get_trt().at(j)->get_t();

                if(this->get_trt().at(i)->get_adj().at(0) == elmt){
                    found = true;
                    break;
                }  
            }
            if (found == false){
                if (this->get_trt().at(i)->get_adj().at(0) != 0){
                    Territoryt* tempt3 = new Territoryt();
                    tempt3->set_t(this->get_trt().at(i)->get_adj().at(0));
                    result_attack.push_back(tempt3);
                }
            }
            else {
                found = false;
            }

            for (int j =0; j < this->get_trt().size(); j++){
                int elmt = this->get_trt().at(j)->get_t();

                if(this->get_trt().at(i)->get_adj().at(1) == elmt){
                    found = true;
                    break;
                }  
            }
            if (found == false){
                if (this->get_trt().at(i)->get_adj().at(1) != 0){
                    Territoryt* tempt4 = new Territoryt();
                    tempt4->set_t(this->get_trt().at(i)->get_adj().at(1));
                    result_attack.push_back(tempt4);
                }
            }
            else {continue;}
            
        }
        

        else { continue; }
    
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

    std::string order1;
    std::cout <<"Enter order to be added: " ;
    std::cin >> order1;
    std::cout << std::endl;

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
