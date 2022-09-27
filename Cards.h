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
    Card(const Card& o);
    // Plays the card, removes it from the given hand, re-adds it to the deck
    void play(Hand* hand, Deck* deck);
    // Returns the Card's type
    std::string getType();
private:
    std::string type;
    friend std::ostream& operator<<(std::ostream& strm, const Card& card);
};


class Deck {
public:
    // Default constructor. Initializes the deck randomly
    Deck();
    Deck(const Deck& o);
    ~Deck();
    // Stream insertion operator friend
    friend std::ostream& operator<<(std::ostream& strm, const Deck& deck);
    // Picks the top card of the shuffled deck and removed it from the deck
    Card* draw();
    // Adds the given card to the list
    void insert(Card* card);
private:
    std::vector<Card*> cards;
    void shuffle();
};


class Hand {
public:
    Hand();
    void addCard(Card* card);
    const std::vector<Card*>& cardList();
    bool returnToDeck(Card* card, Deck* deck);
    friend std::ostream& operator<<(std::ostream& strm, const Hand& deck);
private:
    std::vector<Card*> cards;
};