#include "gamecontroller.h"

GameController::GameController() {}

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
