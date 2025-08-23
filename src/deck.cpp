#include "deck.h"

Deck::Deck()
{

}

void Deck::createDeck()
{
    for (int suit = 0; suit < static_cast<int>(Suit::Count); ++suit)
    {
        for (int rank = 0; rank <= static_cast<int>(Rank::King); ++rank)
        {
            cards.push_back(Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
        }
    }
}

void Deck::displayDeck()
{
    for (const Card& card : cards)
    {
        card.display();
    }
}


