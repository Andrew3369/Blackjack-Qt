#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "deck.h"
#include "player.h"
#include "dealer.h"

#include <chrono>

constexpr int g_BLACKJACK = 21;
constexpr int g_DEALER_STAND_THRESHOLD = 17;

class GameController
{
private: // might not need pointers
    Deck* deck;
    Player* player;
    Dealer* dealer;

public:
    GameController();
    ~GameController();
    Player* getPlayer() const {return player;}
    Dealer* getDealer() const {return dealer;}

    void startGame();
    void resetGame();
    void playerHit();
    void playerStand();
    void dealerTurn();
    void gameConditions();
};

#endif // GAMECONTROLLER_H
