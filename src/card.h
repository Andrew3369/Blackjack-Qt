#ifndef CARD_H
#define CARD_H

#define g_RankNotFound "RANK_ERROR";
#define g_SuitNotFound "SUIT_ERROR";

#include <iostream>
#include <QString>

#define g_cardsFilePath ":/assets/cards/"
#define g_invalidRank -1

enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades,
    Count,
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
private:
    Suit suit;
    Rank  rank;
    //void getRank();
    std::string getRank() const;
    std::string getSuit() const;


public:
    Card(Suit s, Rank r) : suit(s), rank(r) {}
    void display() const;
    const std::string displayCmd();
    uint8_t getValue() const;
    //std::string getSuit() const;
    //std::string getRank() const;
    QString toFilename() const;
};

#endif // CARD_H
