#include <iostream>
#include <sstream>
#include "blackjackPlayer.h"
#include "blackjackHand.h"
#include "blackjackDeck.h"
#include "blackjackBank.h"

/*Andy Yee (24499586)
*Project 1
*ECE 373
*/
using namespace std;

class blackjackHand;
class blackjackBank;
class blackjackDeck;

blackjackPlayer::blackjackPlayer(blackjackDeck d){
    deck = d;
    blackjackHand temp(deck);
    hand = temp;
    blackjackBank temp2(2000);
    bank = temp2;
}
void blackjackPlayer::getDeck(blackjackDeck d){
	deck = d;
	blackjackHand temp(deck);
	hand = temp;
}
void blackjackPlayer::getAmount(int credits){
	blackjackBank temp2(credits);
	bank = temp2;
}

void blackjackPlayer::bet(int betAmount){
    bank.updateTotal(-betAmount);
    }
void blackjackPlayer::hit(){
    hand.addCard();
}
void blackjackPlayer::doubleDown(){/*zZzZzZ*/}
void blackjackPlayer::split(){/*zzzzzz*/}
bool blackjackPlayer::stand(){ return true; }
bool blackjackPlayer::surrender(){ return true; }
void blackjackPlayer::newHand(blackjackDeck d){
    deck = d;
    blackjackHand temp(deck);
    hand = temp;
}


