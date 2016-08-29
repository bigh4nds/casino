#include "blackjackHand.h"
#include "blackjackCard.h"
#include "blackjackDeck.h"
#include <iostream>

// Initializes blackjackHand
blackjackHand::blackjackHand(blackjackDeck d){
    sum = 0;
    numCards = 2;
    deck = d;
    card[0] = getCard();
    card[1] = getCard();
    //aceCt = 0;
    updateTotal();
}

blackjackHand::blackjackHand(){}

// Initializer for second hand in split situation
blackjackHand::blackjackHand(blackjackDeck d, blackjackCard c){
    sum = 0;
    numCards = 2;
    deck = d;
    card[0] = c;
    card[1] = getCard();
    //aceCt = 0;
    updateTotal();
}

// Returns sum
int blackjackHand::getValue(){
    return sum;
}

// Returns a card from the deck
blackjackCard blackjackHand::getCard(){
    return deck.dealCard();
}
// Calls for a card to be retrieved from deck & calls updateTotal
void blackjackHand::addCard(){
    if(numCards<5){
        card[numCards] = getCard();
        numCards++;
        updateTotal();
    }
}

// Splits current hand & returns new second hand
blackjackHand blackjackHand::splitHand(){
    blackjackHand temp(deck,card[1]);
    card[1] = getCard();
    return temp;
}

// Updates total
// Handles Ace card values here.
void blackjackHand::updateTotal(){
    sum = 0;
    for (int i=0; i < numCards; i++){
        sum += card[i].value;
    }

    for(int x = 0; x < numCards; x++){
        if(card[x].value == 11 && sum > 21){
        sum -= 10;
        }
    }

}

blackjackDeck blackjackHand::updateDeckToGame() { return deck; }
void blackjackHand::updateDeckToTable(blackjackDeck d){
    deck = d;
}
