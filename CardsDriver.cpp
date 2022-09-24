#include <iostream>
#include "Cards.h"

using std::cout; using std::endl; using std::string;

void testCards() {
    cout << "Testcards" << endl;
    Deck* deck = new Deck();
    cout << *deck << endl;
}