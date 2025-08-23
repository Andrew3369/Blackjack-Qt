#ifndef CARD_H
#define CARD_H
#include "gameengine.h"

#define g_rankError "RANK_ERROR";
#define g_suitError "SUIT_ERROR";


enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades,
    Count
};
enum class Rank
{
    Ace,
    Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack,
    Queen,
    King,
};

class Card
{
    //Q_OBJECT
private:
    Suit suit;
    Rank  rank;

public:
    Card(Suit s, Rank r) : suit(s), rank(r) {}
    void display() const;
    int getValue() const;
    std::string getSuit() const;
    std::string getRank() const;
};

#endif // CARD_H
