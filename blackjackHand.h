#ifndef BLACKJACKHAND_H
#define BLACKJACKHAND_H

#include "blackjackCard.h"
#include "blackjackDeck.h"

class blackjackHand{
    private:
    blackjackDeck deck;
    int sum;
    //int aceCt;
    void updateTotal();
    blackjackCard getCard();
    blackjackHand(blackjackDeck,blackjackCard);

    public:
    int numCards;
    blackjackCard card[5];
    blackjackHand();
    blackjackHand(blackjackDeck);
    int getValue();
    void addCard();
    blackjackHand splitHand();
    blackjackDeck updateDeckToGame();
    void updateDeckToTable(blackjackDeck);
};

#endif
