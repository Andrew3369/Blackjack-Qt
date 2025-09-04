#include "player.h"

Player::Player()
{

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

int Player::getTotalValue() const
{
    int total = 0;
    for (const Card& card : hand)
    {
        total += card.getValue();
    }
    return total;
}

void Player::removeCards()
{
    hand.clear();
}
