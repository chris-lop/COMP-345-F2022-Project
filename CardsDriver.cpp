#include <iostream>
#include "Cards.h"

using std::cout, std::endl, std::string;

void testCards() {
    cout << "In testcards" << endl;
    Card card("diplomacy");
    card.play();
}