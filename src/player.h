#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <qdebug.h>
#include "card.h"

class Player
{

private:
    std::vector<Card> hand;
    uint16_t chipsBalance;
    bool doubledDown;

public:
    Player();

    void displayHand();
    std::vector<Card> getHand();
    void addCard(Card card);
    uint8_t getTotalValue() const;
    void removeCards();
    bool doubleDown();
    void toggleDoubledDown();
};

#endif // PLAYER_H
