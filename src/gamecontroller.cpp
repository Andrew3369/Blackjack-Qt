#include "gamecontroller.h"

GameController::GameController()
{
    player = new Player();
    dealer = new Dealer();
    deck = new Deck();
}

GameController::~GameController()
{
    delete player;
    delete dealer;
    delete deck;
}

void GameController::startGame()
{
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
}

void GameController::resetGame()
{
    player->removeCards();
    dealer->removeCards();
}

void GameController::playerHit()
{
    player->addCard(deck->dealCard());
    switch (gameConditions(false))
    {
        case GameState::PlayerWin:
            qDebug() << "Player has: " + QString::number(player->getTotalValue())+ " , Player wins";
            return;

        case GameState::DealerWin:
            qDebug() << "Player has: " + QString::number(player->getTotalValue())+ " , Player wins";
            return;

        case GameState::Draw:
            qDebug() << "Push, Player and Dealer same count";
            return;

        case GameState::Error:
            qDebug() << "ERROR";
            return;
    }
}

void GameController::dealerHit()
{
    dealer->addCard(deck->dealCard());
}

void GameController::playerStand(UiController& uiCtrl)
{
    //uiCtrl.showDealerHand(dealer->getHand(), true);
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    while (dealer->getTotalValue() < g_DEALER_STAND_THRESHOLD)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        dealerHit();
        uiCtrl.showDealerHand(dealer->getHand(), true);
        gameConditions(true);
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    //uiCtrl.getResetButton()->show();
}

GameState GameController::gameConditions(bool playerStand)
{
    if (playerStand)
    {
        // figure this one out lol
        if (dealer->getTotalValue() == player->getTotalValue())
            return GameState::Draw;
        else if (dealer->getTotalValue() == g_BLACKJACK)
            return GameState::DealerWin;
        else if (dealer->getTotalValue() > g_BLACKJACK)
            return GameState::PlayerWin;
        // can probably combine these 2 later
        else if (dealer->getTotalValue() > player->getTotalValue())
            return GameState::DealerWin;
        else if (player->getTotalValue() > dealer->getTotalValue())
            return GameState::PlayerWin;
    }
    else
    {
        if (player->getTotalValue() == g_BLACKJACK)
            return GameState::PlayerWin;

        // could probably throw rthis into a else clause
        else if (player->getTotalValue() > g_BLACKJACK)
            return GameState::DealerWin;
    }
    return GameState::Error;
}

