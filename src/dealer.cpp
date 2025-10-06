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

uint8_t Dealer::getTotalValue()
{
    uint8_t total = 0;
    for (const Card& card : hand)
    {
        total += card.getValue();
    }
    return total;
}

uint8_t Dealer::getFirstCardTotal()
{
    return hand[0].getValue();
}
