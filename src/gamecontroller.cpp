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
        //gameConditions(true);
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

GameState GameController::gameConditions(bool playerStand)
{
    if (playerStand)
    {
        if (dealer->getTotalValue() > g_BLACKJACK)
            return GameState::DealerBust;
        else if (dealer->getTotalValue() == player->getTotalValue())
            return GameState::Draw;
        else if (dealer->getTotalValue() == g_BLACKJACK)
            return GameState::DealerWin;
        else if (dealer->getTotalValue() > player->getTotalValue())
            return GameState::DealerWin;
        else if (dealer->getTotalValue() < player->getTotalValue())
            return GameState::PlayerWin;
    }
    else
    {
        if (player->getTotalValue() > g_BLACKJACK)
            return GameState::PlayerBust;
        else if (player->getTotalValue() == g_BLACKJACK)
            return GameState::PlayerWin;
    }
    return GameState::Error;
}

