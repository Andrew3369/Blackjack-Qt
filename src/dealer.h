#ifndef DEALER_H
#define DEALER_H

#include "player.h"

class Dealer : public Player
{

private:
    std::vector<Card> hand;


public:
    Dealer();
    void displayOneCard();
    void displayFullHand();
};

#endif // DEALER_H
