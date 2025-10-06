#ifndef DEALER_H
#define DEALER_H
#include <vector>

#include "card.h"

class Dealer
{
private:
    std::vector<Card> hand;

public:
    Dealer();
    void displayOneCard();
    void displayFullHand();
    uint8_t getFirstCardTotal();
    uint8_t getTotalValue();
    std::vector<Card> getHand();
    void addCard(Card card);
    void removeCards();
};

#endif // DEALER_H
