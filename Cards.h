#include <string>
#include <vector>
#include <iostream>

// Driver function
void testCards();

// Class definitions
class Card
{
private:
    std::string type;
    friend std::ostream& operator<<(std::ostream& strm, const Card& card);
public:
    Card(std::string type);
    void play();
};

class Deck {
public:
    Deck();
    friend std::ostream& operator<<(std::ostream& strm, const Deck& deck);
private:
    std::vector<Card*> cards;
};

class Hand {

};