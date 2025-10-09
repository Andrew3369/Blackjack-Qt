#include "deck.h"


Deck::Deck()
{
    std::thread CreateDeck(&Deck::createDeck, this);
    CreateDeck.join();
    std::thread shuffleDeck(&Deck::shuffle, this);
    shuffleDeck.join();
}

uint32_t Deck::totalDeckSize() const
{
    return cards.size();
}

void Deck::createDeck()
{
    for (int suit = 0; suit < static_cast<int>(Suit::Count); ++suit)
        for (int rank = 0; rank <= static_cast<int>(Rank::King); ++rank)
            cards.push_back(Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));

    //std::cout << totalDeckSize();
}

void Deck::shuffle()
{
    std::random_device randomD;
    std::mt19937 g(randomD());
    std::shuffle(cards.begin(), cards.end(), g);
}

void Deck::displayDeck()
{
    for (const Card& card : cards)
        card.display();

}

Card Deck::dealCard()
{
    if (!cards.empty())
    {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
    else
        // not sure how to handle an empty deck
        return Card(Suit::Spades, Rank::Seven);
}


