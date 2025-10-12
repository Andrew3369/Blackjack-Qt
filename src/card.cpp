#include "card.h"

void Card::display() const
{
    std::cout << getSuit() << " " << getRank() << std::endl;
}

const std::string Card::displayCmd() const
{
    return getSuit() + " " + getRank();
}

// TODO:
// put a bool val here to indicate whether the player has a soft hand or not
uint8_t Card::getValue() const
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

        // TODO: either 1 or 11
        case Rank::Ace:
            return 11;


        default: return g_invalidRank;
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
        case Rank::Ace: return "Ace";
        default: return g_RankNotFound;
    }
}

QString Card::toFilename() const
{
    QString rankStr, suitStr = "";

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
    {
        case Suit::Hearts:  suitStr = "hearts";
        case Suit::Diamonds: suitStr = "diamonds";
        case Suit::Clubs: suitStr = "clubs";
        case Suit::Spades: suitStr = "spades";
        //default: suitStr = "no file";
    }
    return rankStr + "_" + suitStr + ".png";
}
