/*
    Dealer.cpp
    C++ file for Dealer class
*/

#include <stdio.h>
#include "blackjackDealer.h"
#include "blackjackHand.h"

using namespace std;

class blackjackHand;
class blackjackDeck;

blackjackDealer::blackjackDealer(blackjackDeck d){
    deck = d;
    blackjackHand temp(deck);
    hand = temp;
}

blackjackDealer::blackjackDealer(){}

void blackjackDealer::getDeck(blackjackDeck d){
	deck = d;
	blackjackHand temp(deck);
	hand = temp;
}

void blackjackDealer::playHand(){
    while(hand.getValue() < 17){
    hand.addCard();
    //displayCard();
    }
    if(hand.getValue() > 21)
        status = 0;
    else if(hand.getValue() == 21)
        status = 1;
    else
        status = 2;
}

int blackjackDealer::getStatus(){
    return status;
}

void blackjackDealer::newHand(blackjackDeck d){
    deck = d;
    blackjackHand temp(deck);
    hand = temp;
}
