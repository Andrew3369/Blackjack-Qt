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

// might not need this, or somehow
// communicate uictrl with gamectrl in here
void GameController::playerStand()
{
    // line 373 mainwindow.cpp
}

void GameController::dealerTurn()
{
    // might not need while since we cant update ui from here
    //while (dealer->getTotalValue() < 17)

    dealer->addCard(deck->dealCard());
}

//GameState GameController::gameConditions(bool playerStand)
bool GameController::gameConditions(bool playerStand)
{
    if (playerStand)
    {
        // figure this one out lol
        if (dealer->getTotalValue() == player->getTotalValue())
        {
            qDebug() << "Push! No winner";
        }
        else if (dealer->getTotalValue() == g_BLACKJACK)
        {
            qDebug() << "Dealer has Blackjack!";
            return false;
        }
        else if (dealer->getTotalValue() > g_BLACKJACK)
        {
            qDebug() << "Dealer busts! Player wins";
            return true;
        }
        // can probably combine these 2 later
        else if (dealer->getTotalValue() > player->getTotalValue())
        {
            qDebug() << "Dealer has higher count! Dealer wins";
            return false;
        }
        else if (player->getTotalValue() > dealer->getTotalValue())
        {
            qDebug() << "Player wins!";
            return true;
        }
    }
    else
    {
        if (player->getTotalValue() == g_BLACKJACK)
        {
            qDebug() << "Player has blackjack! Starting dealer stand logic...";
            return true;
        }
        else if (player->getTotalValue() > g_BLACKJACK)
        {
            qDebug() << "Player over 21";
            return false;
        }
    }
    return ERROR;
}

