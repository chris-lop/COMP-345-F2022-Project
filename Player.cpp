#include <iostream> 
#include "Player.h"

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
    set_adj(arr);
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

std::vector <int> Territoryt::get_adj() {
    return this->adj;
}


/*
* Temporary Card class
*/
Cardt::Cardt() {
    set_ctype("null");
}

Cardt::Cardt(std::string ctype) {
    set_ctype(ctype);
}

void Cardt::set_ctype(std::string ctype) {
    this->ctype = ctype;
}

std::string Cardt::get_ctype() {
    return this->ctype;
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

/*
* Player class
*/
//Default constructor
Player::Player() {
    this->name = "Null";
    this->trt = {};
    this->hand = {};
    this->olst = {};
}
Player::~Player() {
    for (Territoryt* t: trt) {
        delete(t);
    }
    for (Cardt* c:hand) {
        delete(c);
    }
    for (Ordert* o: olst) {
        delete(o);
    }
}
//Constructor with parameter
Player::Player(std::string name, std::vector<Territoryt*> trt, std::vector<Cardt*> hand, std::vector <Ordert*> olst) {
    this->name = name;
    this->trt = trt;
    this->hand = hand;
    this->olst = olst;
}

//Copy constructor
Player :: Player(const Player& p1){
    this->name = p1.name;
    this->trt = p1.trt;
    this->hand = p1.hand;
    this->olst = p1.olst;
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

//Player stream operators

std::ostream& operator << (std::ostream& strm, const Player& p){
    strm << "This player is: " << p.name << std::endl;
    strm <<"Territoryt owned: ";
    for (int i = 0; i < p.trt.size(); i++) {
        strm << p.trt.at(i)->get_t() << "\t" ;
    } 
    strm << std::endl;

    strm << "Player's current hand of cards: ";
        for (int i = 0; i < p.hand.size(); i++) {
        strm << p.hand.at(i)->get_ctype() << "\t" ;
    } 
    strm << std::endl;

    
    strm << "Player's current list of orders: ";
    for (int i = 0; i < p.olst.size(); i++) {
        std::cout << p.olst.at(i)->get_type() << "\t";
    }
    return strm;
}

std::istream& operator >> (std::istream& in, Player& p){
    std::cout << "Enter player name: ";
    in >> p.name;
    return in;
}

//setter
void Player::set_Order(std::vector <Ordert*> newolst){
    this->olst = newolst;
}

//required methods for assignment 1
void Player::toDefend() {
    
    std::cout << "The player " << this->get_name() << " must defend the following territories: ";
    
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
                std::cout << this->get_trt().at(i)->get_t() << "\t"; 
            }
            else {
                std::cout << this->get_trt().at(i)->get_t() << "\t"; 
            }
        }
    
    }
}

void Player::toAttack(){
    std::cout << "The player " << this->get_name() << " can attack the following territories: ";

    std::vector <int> l1; 
    
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
                    l1.push_back(this->get_trt().at(i)->get_adj().at(0));
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
                    l1.push_back(this->get_trt().at(i)->get_adj().at(1));
                }
            }

            else {continue;}
            
        }
        

        else { continue; }
    
    }

    for (int k = 0; k < l1.size(); k++){
        std::cout << l1.at(k) << "\t"; 
    }

}

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
        newolst.push_back(this->get_olst().at(1));
    }
    newolst.push_back(o1);

    this->set_Order(newolst);

    std::cout << "The new list of order is: ";
        for (int i = 0; i < this->get_olst().size(); i++) {
        std::cout << this->get_olst().at(i)->get_type() << "\t";
    }
}
