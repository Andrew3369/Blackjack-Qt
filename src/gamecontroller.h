#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "deck.h"
#include "player.h"
#include "dealer.h"
#include "uicontroller.h"

#include <chrono>

constexpr uint8_t g_BLACKJACK = 21;
constexpr uint8_t g_DEALER_STAND_THRESHOLD = 17;
#define ERROR -1;

enum class GameState
{
    PlayerWin,
    DealerWin,
    PlayerBust,
    DealerBust,
    Draw,
    Blackjack,
    NoState,
    Error,
    // maybe blackjack?
};

class GameController
{

private:
    Deck* deck;
    Player* player;
    Dealer* dealer;
    GameState gameState;

public:
    GameController();
    ~GameController();
    Player* getPlayer() const {return player;}
    Dealer* getDealer() const {return dealer;}
    GameState getGameState() const {return gameState;}

    void startGame();
    void resetGame();
    void playerHit();
    void dealerHit();
    void playerStand(UiController& uiCtrl);
    GameState gameConditions(bool playerStand);

};

#endif // GAMECONTROLLER_H
