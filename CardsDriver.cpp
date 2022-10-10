#include <iostream>
#include "Cards.h"
#include "Orders.h"

using std::cout; using std::endl; using std::string;


void testCards() {
    // Create initial deck, list, and hand
    cout << endl << endl << "### Test cards ###" << endl;
    Deck* deck = new Deck();
    OrdersList* list = new OrdersList();
    Hand* hand = new Hand();
    
    // Show that the hand and list are empty, and show the list is full
    cout << "# State of the hand, deck, and list of orders: #" << endl;
    cout << *hand << endl;
    cout << *deck << endl;
    cout << *list << endl;

    cout << endl << "# Calling draw() to get 5 cards #" << endl;
    cout << "These 5 cards should be removed from the deck and placed in the hand." << endl;
    cout << "# Adding cards: ";
    // Draw 5 random cards from the deck and add them to the hand
    for (int i = 0; i < 5; i++) {
        Card* card = deck->draw();
        // Show the drawn card
        cout << *card << " ";
        hand->addCard(card);
    }
    // Show that the 5 cards have moved from the deck to the hand
    cout << " #" << endl;
    cout << *hand << endl;
    cout << *deck << endl;
    cout << endl;
    
    // play each card
    cout << "# Now, calling play() on each of the cards in the hand. #" << endl;
    cout << "This should put it in the list of orders, and return it to the deck." << endl << endl;
    while (hand->cardList().size() > 0) {
        hand->cardList().back()->play(hand, deck, list);
    }
    cout << endl;

    // Show that the orders have been added to the list,
    // and that the cards are back in the deck
    cout << "# State of the hand, deck, and list of orders: #" << endl;
    cout << *hand << endl;
    cout << *deck << endl;
    cout << *list << endl;

    cout << endl << endl;
    // Delete pointers
    delete deck; delete list; delete hand;
}