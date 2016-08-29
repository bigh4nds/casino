 /** blackjackBank class source
  ** handles player's money/chips
  ** author: Christopher Finn
  **/

#include <iostream>
#include "blackjackBank.h"
using namespace std;

int BankTotal;

blackjackBank::blackjackBank(){}

// Initializes blackjackBank object with initAmount
blackjackBank::blackjackBank(int initAmount){
	BankTotal = initAmount;
}

// Returns blackjackBankTotal
int blackjackBank::getTotal(){
	return BankTotal;
}

// Updates total by +dif
void blackjackBank::updateTotal(int dif){
	if(BankTotal + dif < 0)
        BankTotal = 0;
    else
        BankTotal += dif;
}

// Prints "$" + blackjackBankTotal
int blackjackBank::returnTotal(){
	return BankTotal;
}
