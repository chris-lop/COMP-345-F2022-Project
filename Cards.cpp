#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <vector>
#include <ctime>

using std::cout; using std::endl; using std::string; using std::vector;

/**
 * Card class
 */

// Play method. Creates an order, places it in the list of orders,
// removed it from the given hand, and places it back in the deck.
void Card::play(Hand* hand, Deck* deck, OrdersList* list) {
    Order* order = nullptr;
    // Constructs an order (or not) based on the card's type.
    if (type == "bomb") {
        order = new Bomb();
    } else if (type == "reinforcement") {
        cout << "Reinforcement card played, no order created." << endl;
    } else if (type == "blockade") {
        order = new Blockade();
    } else if (type == "airlift") {
        order = new Airlift();
    } else if (type == "diplomacy") {
        order = new Negotiate();
    }
    if (order != nullptr) {
        // If an order was constructed, add to orderlist
        cout << "order added: " << *order << endl;
        list->addOrder(order);
    }
    // Removes it from the hand and places it in the deck
    hand->returnToDeck(this, deck);
}

// Returns the type of the card
std::string Card::getType() {
    return type;
}

// Card constructor, takes a type
Card::Card(string type): type(type) {
}

// Copy constructor
Card::Card(const Card& o):type(o.type) {
}

// Card destructor. Only member is a string, (manages its own memory)
// so no manual deletes needed.
Card::~Card() {
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& strm, const Card& card) {
    return strm << card.type << " card";
}

// Assignment operator for Card
Card& Card::operator=(const Card &rightSide) {
    type = rightSide.type;
    return *this;
}

/**
 * Deck class
 */

// Picks the top card, removes from the deck, and returns it
Card* Deck::draw() {
    // cerr << "cards size: " << cards.size() << endl;
    if (cards.size() == 0) {
        return nullptr;
    }
    Card* card = cards.back();
    cards.pop_back();
    return card;
}

// Adds card to the deck
void Deck::insert(Card* card) {
    cards.push_back(card);
    shuffle();
}

// Stores the card types, to allow the Deck default constructor to create a starter deck
vector<string> types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
// The ctor uses this list to determine the number of cards of each type to add to the deck
vector<int> numberOfEach = {3, 3, 3, 3, 3};

// Deck constructor
Deck::Deck() {
    // Loop over the types of cards and add to deck the correct number of times
    for (int i = 0; i < types.size(); i++) {
        for (int j = 0; j < numberOfEach[j]; j++) {
            Card* card = new Card(types[i]);
            cards.push_back(card);
        }
    }
    shuffle();
}

// Constructs a deck with the given cards. The cards are *copied*.
Deck::Deck(std::vector<Card*> newCards) {
    cards = vector<Card*>();
    for (Card* c: newCards) {
        cards.push_back(new Card(*c));
    }
}

// Copy constructor. *Copies* the cards from the other deck.
Deck::Deck(const Deck& o) {
    cards = vector<Card*>();
    for (Card* c: o.cards) {
        cards.push_back(new Card(*c));
    }
}

// Destructor. Deletes all cards
Deck::~Deck() {
    for (Card* c: cards) {
        delete(c);
    }
}

// Shuffles the deck using the srand function.
void Deck::shuffle() {
    srand(time(NULL)); // initialize with current unix time as seed
    const int randMax = cards.size();
    for (int i = 0; i < cards.size(); i++) {
        // swap cards randomly
        int otherSwap = rand() % randMax;
        Card* temp = cards[i];
        cards[i] = cards[otherSwap];
        cards[otherSwap] = temp;
    }
}

// Stream insertion operator for Deck
std::ostream& operator<<(std::ostream& strm, const Deck& deck) {
    strm << "Deck: ";
    // Print out each Card
    for (int i = 0; i < deck.cards.size(); i++) {
        Card& cardRef = *(deck.cards[i]);
        strm << cardRef;
        // Add commas after every Card except the last
        if (i < deck.cards.size() - 1) {
            strm << ", ";
        }
    }
    return strm;
}

// Like the copy constructor, *copies* the cards over
Deck& Deck::operator=(const Deck &rightSide) {
    cards = vector<Card*>();
    for (Card* c: rightSide.cards) {
        cards.push_back(new Card(*c));
    }
    return *this;
}

/**
 * Hand methods
 */

// Default ctor. Leaves the card list empty.
Hand::Hand(){
    cards = {};
}

// Adds card to list. Card is *not copied*, and this class
// *will delete it* when its destructor is called.
void Hand::addCard(Card* card) {
    cards.push_back(card);
}

// Accessor
vector<Card*> Hand::getCards()
{
    return this->cards;
}

// Mutator
void Hand::setCards(vector<Card*> newCards)
{
    this->cards = newCards;
}

// Returns a const reference to the cards the Hand holds
const vector<Card*>& Hand::cardList() {
    return cards;
}

// Puts the given card in the deck. Only does this
// if the *card is in this hand*.
// Returns whether or not the card was moved.
bool Hand::returnToDeck(Card* card, Deck* deck) {
    vector<Card*>::iterator itr;
    for (itr = cards.begin(); itr < cards.end(); itr++) {
        if (*itr == card) {
            deck->insert(*itr);
            cards.erase(itr);
            return true;
        }
    }
    return false;
}

// Prints a description of this Hand on the given stream
std::ostream& operator<<(std::ostream& strm, const Hand& hand) {
    strm << "Hand: ";
    if (hand.cards.size() == 0) {
        strm << "[empty]";
    } else {
        // Loop over each card and print it on the stream
        for (int i = 0; i < hand.cards.size(); i++) {
            Card& cardRef = *(hand.cards[i]);
            strm << cardRef;
            if (i < hand.cards.size() - 1) {
                strm << ", ";
            }
        }
    }
    return strm;
}

// Assignment operator. Like the copy constructor,
// *copies all cards*.
Hand& Hand::operator=(const Hand &rightSide) {
    cards = vector<Card*>();
    for (Card* c: rightSide.cards) {
        cards.push_back(new Card(*c));
    }
    return *this;
}

// Copy constructor. *Copies all cards*.
Hand::Hand(const Hand& h) {
    cards = vector<Card*>();
    for (Card* c: h.cards) {
        cards.push_back(new Card(*c));
    }
}

// Destructor. *Deletes all cards*.
Hand::~Hand() {
    for (Card* c: cards) {
        delete(c);
    }
}