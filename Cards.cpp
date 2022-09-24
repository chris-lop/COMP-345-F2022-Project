#include "Cards.h"
#include <iostream>
#include <vector>

using std::cout, std::endl, std::string, std::vector;

// For Card class

void Card::play() {
    cout << "In Card::play. Card type is " << type << " " << std::endl;
}

Card::Card(string type): type(type) {
}

std::ostream& operator<<(std::ostream& strm, const Card& card) {
    return strm << card.type << " card";
}

// For Deck class
vector<string> types = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};
vector<int> numberOfEach = {3, 3, 3, 3, 3};
Deck::Deck() {
    for (int i = 0; i < types.size(); i++) {
        for (int j = 0; j < numberOfEach[j]; j++) {
            Card* card = new Card(types[i]);
            cards.push_back(card);
        }
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