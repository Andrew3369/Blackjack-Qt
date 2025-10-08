#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "deck.h"
#include "player.h"
#include "dealer.h"

#include <chrono>

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

    void StartGame();
    void ResetGame();
    void PlayerHit();
    void PlayerStand();
    void DealerTurn();
};

#endif // GAMECONTROLLER_H
