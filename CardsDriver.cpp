#include <iostream>
#include "Cards.h"

using std::cout; using std::endl; using std::string;

void testCards() {
    cout << "Test cards" << endl;
    Deck* deck = new Deck();
    cout << *deck << endl;

    cout << endl << "Creating hand" << endl;
    Hand* hand = new Hand();
    cout << "Adding 5 cards" << endl << endl;
    for (int i = 0; i < 5; i++) {
        hand->addCard(deck->draw());
    }
    cout << *hand << endl;
    cout << *deck << endl;
    cout << endl << endl;
}