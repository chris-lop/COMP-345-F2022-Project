#include <iostream>
#include "Cards.h"

using std::cout; using std::endl; using std::string;

void testCards() {
    cout << "### Test cards ###" << endl;
    Deck* deck = new Deck();
    cout << *deck << endl;

    Hand* hand = new Hand();
    cout << endl << "# Creating hand, adding 5 cards #" << endl << endl;
    for (int i = 0; i < 5; i++) {
        hand->addCard(deck->draw());
    }
    cout << *hand << endl;
    cout << *deck << endl;

    cout << endl;
    
    cout << "# Now, calling play() on each of the cards #" << endl;
    while (hand->cardList().size() > 0) {
        hand->cardList().back()->play(hand, deck);
    }
    cout << endl;

    cout << "# State of the hand and deck: #" << endl;
    cout << *hand << endl;
    cout << *deck << endl;

    cout << endl << endl;
}