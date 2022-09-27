#include "Cards.h"
#include <iostream>
#include <vector>
#include <ctime>

using std::cout; using std::endl; using std::string; using std::vector;

/**
 * Card class
 */

void Card::play(Hand* hand, Deck* deck) {
    cout << "In Card::play, " << *this << endl;
    hand->returnToDeck(this, deck);
}

Card::Card(string type): type(type) {
}

Card::Card(const Card& o):type(o.type) {
}

std::ostream& operator<<(std::ostream& strm, const Card& card) {
    return strm << card.type << " card";
}

std::string Card::getType() {
    return type;
}

/**
 * Deck class
 */

Card* Deck::draw() {
    Card* card = cards.back();
    cards.pop_back();
    return card;
}

void Deck::insert(Card* card) {
    cards.push_back(card);
    shuffle();
}

vector<string> types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
vector<int> numberOfEach = {3, 3, 3, 3, 3};

Deck::Deck() {
    for (int i = 0; i < types.size(); i++) {
        for (int j = 0; j < numberOfEach[j]; j++) {
            Card* card = new Card(types[i]);
            cards.push_back(card);
        }
    }
    shuffle();
}

Deck::Deck(const Deck& o) {
    cards = vector<Card*>();
    for (Card* c: o.cards) {
        cards.push_back(new Card(*c));
    }
}

Deck::~Deck() {
    for (Card* c: cards) {
        delete(c);
    }
}

void Deck::shuffle() {
    srand(time(NULL));
    const int randMax = cards.size();
    for (int i = 0; i < cards.size(); i++) {
        int otherSwap = rand() % randMax;
        Card* temp = cards[i];
        cards[i] = cards[otherSwap];
        cards[otherSwap] = temp;
    }
}

std::ostream& operator<<(std::ostream& strm, const Deck& deck) {
    strm << "Deck: ";
    for (int i = 0; i < deck.cards.size(); i++) {
        Card& cardRef = *(deck.cards[i]);
        strm << cardRef;
        if (i < deck.cards.size() - 1) {
            strm << ", ";
        }
    }
    return strm;
}

/**
 * Hand methods
 */

Hand::Hand(){
}

void Hand::addCard(Card* card) {
    cards.push_back(card);
}

const vector<Card*>& Hand::cardList() {
    return cards;
}

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

std::ostream& operator<<(std::ostream& strm, const Hand& hand) {
    strm << "Hand: ";
    if (hand.cards.size() == 0) {
        strm << "[empty]";
    } else {
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