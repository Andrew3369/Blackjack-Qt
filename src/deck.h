#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include "card.h"


class Deck
{
private:
    std::vector<Card> cards;

private:
    void shuffle();
    void createDeck();
    void burnDeck();
    inline uint32_t totalDeckSize() const;

public:
    Deck();
    void displayDeck();
    Card dealCard();
};

#endif // DECK_H
