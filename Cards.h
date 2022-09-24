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
private:
    std::string type;
    friend std::ostream& operator<<(std::ostream& strm, const Card& card);
    void play(Hand hand, Deck deck);
public:
    Card(std::string type);
    void play();
};


class Deck {
public:
    // Default constructor. Initializes the deck randomly
    Deck();
    // Stream insertion operator friend
    friend std::ostream& operator<<(std::ostream& strm, const Deck& deck);
    // Picks the top card of the shuffled deck and removed it from the deck
    Card* draw();
private:
    std::vector<Card*> cards;
    void shuffle();
};


class Hand {
public:
    Hand();
    void addCard(Card* card);
    const std::vector<Card*>& cardList();

    friend std::ostream& operator<<(std::ostream& strm, const Hand& deck);
private:
    std::vector<Card*> cards;
};