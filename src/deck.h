#ifndef DECK_H
#define DECK_H

#include "gameengine.h"
#include "card.h"

#include <thread>

class Deck
{
private:
    std::vector<Card> cards;

private:
    void shuffle();
    void createDeck();
    void burnDeck();

public:
    Deck();
    void displayDeck();
    Card dealCard();
};

#endif // DECK_H
