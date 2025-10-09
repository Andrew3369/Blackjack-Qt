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

void GameController::gameConditions()
{

}

