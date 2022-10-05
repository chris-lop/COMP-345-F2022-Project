#include <iostream>
#include "Cards.h"

using std::cout; using std::endl; using std::string;

//#define BONUS_CARD_TEST

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

    #ifdef BONUS_CARD_TEST
    cout << endl << "# Bonus: test operator= and copy ctor for Card #" << endl;
    Card c1("test type");
    Card c2 = c1;
    Card c3(c1);
    cout << "c1: " << c1 << " c2(assignment): " << c2 << " c3 (copy ctor): " << c3 << endl;

    cout << endl << "# Bonus: test operator= and copy ctor for Deck #" << endl;
    Deck d1({new Card("card1"), new Card("card2"), new Card("card3")});
    Deck d2 = d1;
    Deck d3(d1);
    cout << "d1: " << d1 << endl << "d2(assignment): " << d2 << endl << "d3 (copy ctor): " << d3 << endl;
    cout << "Now, I draw 1 card from d1 and d2 and two from d3" << endl;
    d2.draw();
    d3.draw();
    d3.draw();
    cout << "d1: " << d1 << endl << "d2(assignment): " << d2 << endl << "d3 (copy ctor): " << d3 << endl;

    cout << endl << "# Bonus: test operator= and copy ctor for Hand #" << endl;
    Hand h1;
    Deck d;
    h1.addCard(new Card("card1"));
    h1.addCard(new Card("card2"));
    h1.addCard(new Card("card3"));
    Hand h2(h1);
    Hand h3 = h1;
    cout << "h1: " << h1 << endl << "h2(assignment): " << h2 << endl << "h3 (copy ctor): " << h3 << endl;
    cout << "Now, I draw 1 card from h1 and h2 and two from h3" << endl;
    h1.returnToDeck(h1.cardList()[0], &d);
    h2.returnToDeck(h2.cardList()[0], &d);
    h3.returnToDeck(h3.cardList()[0], &d);
    h3.returnToDeck(h3.cardList()[0], &d);

    cout << "h1: " << h1 << endl << "h2(assignment): " << h2 << endl << "h3 (copy ctor): " << h3 << endl;
    
    #endif

    cout << endl << endl;
}