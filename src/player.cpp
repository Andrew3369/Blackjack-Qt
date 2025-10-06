#include "player.h"


Player::Player()
{
    chipsBalance = 0;
    doubledDown = false;
}

void Player::displayHand()
{
    for (const Card& card : hand)
        card.display();
}

std::vector<Card> Player::getHand()
{
    return hand;
}

void Player::addCard(Card card)
{
    hand.push_back(card);
}

uint8_t Player::getTotalValue() const
{
    uint8_t total = 0;
    for (const Card& card : hand)
    {
        total += card.getValue();
    }
    return total;
}

void Player::removeCards()
{
    try
    {
        hand.clear();
    }
    catch (std::exception& error)
    {
        qDebug() << "couldnt clear hand";
    }
}

bool Player::doubleDown()
{
    return doubledDown;
}

void Player::toggleDoubledDown()
{
    doubledDown = !doubledDown;
}
