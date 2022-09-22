#include "Cards.h"
#include <iostream>

using std::cout, std::endl, std::string;

void Card::play() {
    cout << "In Card::play. Card type is " << type << " " << std::endl;
}

Card::Card(string type): type(type) {
    
}