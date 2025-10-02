#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <qdebug.h>
#include "card.h"

class Player
{

private:
    std::vector<Card> hand;
    int chips;
    bool doubledDown;

public:
    Player();

    void displayHand();
    std::vector<Card> getHand();
    void addCard(Card card);
    int getTotalValue() const;
    void removeCards();
    bool doubleDown();
};

#endif // PLAYER_H
