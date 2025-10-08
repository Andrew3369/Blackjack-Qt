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

void GameController::StartGame()
{
    //deck->shuffle();

    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
}

void GameController::ResetGame()
{
    player->removeCards();
    dealer->removeCards();
}

void GameController::PlayerHit()
{
    player->addCard(deck->dealCard());
}

void GameController::PlayerStand()
{

}

void GameController::DealerTurn()
{
    while (dealer->getTotalValue() < 17)
        dealer->addCard(deck->dealCard());
}
