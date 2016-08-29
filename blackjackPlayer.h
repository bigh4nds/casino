#ifndef BLACKJACKPLAYER_H
#define BLACKJACKPLAYER_H

#include "blackjackBank.h"
#include "blackjackHand.h"
#include "blackjackDeck.h"

class blackjackPlayer
{
    public:
        blackjackBank bank;
        blackjackHand hand;
        blackjackDeck deck;
        blackjackPlayer(blackjackDeck);
	void getDeck(blackjackDeck);
	void getAmount(int);
        void newHand(blackjackDeck);
        void bet(int betAmount);
        void hit();
        bool stand(void);
        void doubleDown(void);
        void split(void);
        bool surrender(void);
        int getChipCount(void);

};

#endif
