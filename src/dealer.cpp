#include "dealer.h"

Dealer::Dealer() {}

std::vector<Card> Dealer::getHand()
{
    return hand;
}

void Dealer::addCard(Card card)
{
    hand.push_back(card);
}

void Dealer::removeCards()
{
    hand.clear();
}

void Dealer::displayOneCard()
{
    // do later
}

int Dealer::getTotalValue()
{
    int total = 0;
    for (const Card& card : hand)
    {
        total += card.getValue();
    }
    return total;
}

// apparently the hand is always empty lmao
int Dealer::getFirstCardTotal()
{
    return hand[0].getValue();
}
