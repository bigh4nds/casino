/*
    blackjackDealer.h
    Header for the blackjackDealer.cpp class
*/
#ifndef BLACKJACKDEALER_H
#define BLACKJACKDEALER_H

#include "blackjackHand.h"
#include "blackjackDeck.h"

class blackjackDealer{
    public:
    int status;
    blackjackHand hand;
    blackjackDeck deck;


    blackjackDealer();
    blackjackDealer(blackjackDeck);
	void getDeck(blackjackDeck);
    void playHand();
    int getStatus();
    void newHand(blackjackDeck);
};
#endif
