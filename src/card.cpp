#include "card.h"

void Card::display() const
{
    std::cout << getSuit() << " " << getRank() << std::endl;
}

// for adding up cards
int Card::getValue() const
{
    switch (rank)
    {
        case Rank::Two: return 2;
        case Rank::Three: return 3;
        case Rank::Four: return 4;
        case Rank::Five: return 5;
        case Rank::Six: return 6;
        case Rank::Seven: return 7;
        case Rank::Eight: return 8;
        case Rank::Nine: return 9;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King: return 10;
        case Rank::Ace:
            //if (player.getHandSize() <)
            return 11; // not sure how to handle if the Ace is either 1 or 11
        default: return g_ERROR;
    }
}

std::string Card::getSuit() const
{
    switch(suit)
    {
        case Suit::Hearts:  return "Hearts";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Clubs: return "Clubs";
        case Suit::Spades: return "Spades";
        default: return g_suitError;
    }
}

std::string Card::getRank() const
{
    switch (rank)
    {
        case Rank::Two: return "2";
        case Rank::Three: return "3";
        case Rank::Four: return "4";
        case Rank::Five: return "5";
        case Rank::Six: return "6";
        case Rank::Seven: return "7";
        case Rank::Eight: return "8";
        case Rank::Nine: return "9";
        case Rank::Ten: return "10";
        case Rank::Jack: return "J";
        case Rank::Queen: return "Q";
        case Rank::King: return "K";
        case Rank::Ace:
            //if (player.getHandSize() <)
            return "A"; // not sure how to handle if the Ace is either 1 or 11
        default: return g_rankError;
    }
}
