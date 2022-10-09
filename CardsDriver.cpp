#include <iostream>
#include "Cards.h"
#include "Orders.h"

using std::cout; using std::endl; using std::string;


void testCards() {
    cout << "### Test cards ###" << endl;
    Deck* deck = new Deck();
    OrdersList* list = new OrdersList();
    cout << *deck << endl;

    Hand* hand = new Hand();
    cout << endl << "# Creating hand, adding 5 cards #" << endl;
    cout << "These 5 cards should be removed from the deck and placed in the hand." << endl;
    cout << "# Adding cards: ";
    for (int i = 0; i < 5; i++) {
        Card* card = deck->draw();
        cout << *card << " ";
        hand->addCard(card);
    }
    cout << " #" << endl;
    cout << *hand << endl;
    cout << *deck << endl;
    cout << endl;
    
    cout << "# Now, calling play() on each of the cards in the hand. #" << endl;
    cout << "This should put it in the list of orders, and return it to the deck." << endl << endl;
    while (hand->cardList().size() > 0) {
        hand->cardList().back()->play(hand, deck, list);
    }
    cout << endl;

    cout << "# State of the hand, deck, and list of orders: #" << endl;
    cout << *hand << endl;
    cout << *deck << endl;
    cout << *list << endl;

    cout << endl << endl;
    delete deck; delete list; delete hand;
}