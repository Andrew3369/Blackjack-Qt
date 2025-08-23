#include "card.h"

// not final
void Card::display() const
{
    std::cout << getSuit() << " " << getRank() << std::endl;
}

int Card::getValue() const // for adding up cards
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
        default: return g_invalidRank;
    }
}

std::string Card::getSuit() const
{
    switch(suit)
    { // may have to put these lowercase
        case Suit::Hearts:  return "Hearts";
        case Suit::Diamonds: return "Diamonds";
        case Suit::Clubs: return "Clubs";
        case Suit::Spades: return "Spades";
        default: return g_SuitNotFound;
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
            return "Ace"; // not sure how to handle if the Ace is either 1 or 11
        default: return g_RankNotFound;
    }
}


QString Card::toFilename() const
{
    QString rankStr, suitStr;

    switch(rank)
    {
        case Rank::Two: rankStr = "2"; break;
        case Rank::Three: rankStr = "3"; break;
        case Rank::Four: rankStr = "4"; break;
        case Rank::Five: rankStr = "5"; break;
        case Rank::Six: rankStr = "6"; break;
        case Rank::Seven: rankStr = "7"; break;
        case Rank::Eight: rankStr = "8"; break;
        case Rank::Nine: rankStr = "9"; break;
        case Rank::Ten: rankStr = "10"; break;
        case Rank::Jack: rankStr = "jack"; break;
        case Rank::Queen: rankStr = "queen"; break;
        case Rank::King: rankStr = "king"; break;
        case Rank::Ace: rankStr = "ace"; break;
    }
    switch(suit)
    { // may have to put these lowercase
        case Suit::Hearts:  suitStr = "hearts";
        case Suit::Diamonds: suitStr = "diamonds";
        case Suit::Clubs: suitStr = "clubs";
        case Suit::Spades: suitStr = "spades";
    }
    return rankStr + "_" + suitStr + ".png";
}
