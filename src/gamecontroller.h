#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "deck.h"
#include "player.h"
#include "dealer.h"

class GameController
{
private: // might not need pointers
    Deck* deck;
    Player* player;
    Dealer* dealer;

public:
    GameController();
    const Player& getPlayer() const {return *player;}
    const Dealer& getDealer() const {return *dealer;}

    void StartGame();
    void ResetGame();
    void PlayerHit();
    void PlayerStand();
    void DealerTurn();
};

#endif // GAMECONTROLLER_H
