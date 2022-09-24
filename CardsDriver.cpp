#include <iostream>
#include "Cards.h"

using std::cout, std::endl, std::string;

void testCards() {
    cout << "Testcards" << endl;
    Deck* deck = new Deck();
    cout << *deck;
}