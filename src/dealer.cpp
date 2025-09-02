#include "dealer.h"

Dealer::Dealer() {}

void Dealer::displayOneCard()
{

}

int Dealer::getFirstCardTotal()
{
    if (!hand.empty())
    {
        return hand[0].getValue();
    }
    else
        return NULL;
}
