#pragma once

#include "Orders.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

// Driver function
void testCards();

// Class forward declarations

class Deck;
class Hand;
class Card;

// Class definitions

class Card
{
public:
    // Constructs the a card with the given type
    Card(std::string type);
    // Copy ctor
    Card(const Card& o);
    // Destructor
    ~Card();
    // Assignment operator
    Card& operator=(const Card &rightSide);

    // Plays the card, removes it from the given hand, re-adds it to the deck
    void play(Hand* hand, Deck* deck, OrdersList* list);
    // Returns the Card's type
    std::string getType();
private:
    // Card type
    std::string type;
    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& strm, const Card& card);
};


class Deck {
public:
    // Default constructor. Initializes the deck randomly
    Deck();
    // Other constructor, copies the list into this object
    Deck(std::vector<Card*> cards);
    // Copy constructor and destructor
    Deck(const Deck& o);
    ~Deck();
    // operators
    Deck& operator=(const Deck &rightSide);
    // Stream insertion operator friend
    friend std::ostream& operator<<(std::ostream& strm, const Deck& deck);
    // Picks the top card of the shuffled deck and removed it from the deck
    Card* draw();
    // Adds the given card to the list
    void insert(Card* card);
private:
    // Collection of cards
    std::vector<Card*> cards;
    // Private helper method. Shuffles the cards.
    void shuffle();
};


class Hand {
public:
    // Constructor
    Hand();
    // Copy contructor
    Hand(const Hand& h);
    // Destructor
    ~Hand();
    // Assignment operator
    Hand& operator=(const Hand &rightSide);
    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& strm, const Hand& deck);

    // Accessor
    vector<Card*> getCards();
    // Mutator
    void setCards(vector<Card*>);
    
    // Adds a card
    void addCard(Card* card);
    // Returns a card to the provided deck
    bool returnToDeck(Card* card, Deck* deck);
    // Returns a const reference to the card list
    const std::vector<Card*>& cardList();
private:
    // Collection of Cards the hand owns
    std::vector<Card*> cards;
};