/*
    Pot.cpp
    C++ file for Pot class
*/

#include <stdio.h>
#include <iostream>
#include "blackjackPot.h"

using namespace std;

blackjackPot::blackjackPot(int initValue){
    if(initValue <-32767 || initValue > 32767){}
        //cout << "Initial value out of integer bounds" << endl;
    else if(initValue < 0){}
        //cout << "Cannot have a negative pot value." << endl;
    else
        potValue = initValue;
}

void blackjackPot::addToPot(int addValue){
    int numToAdd = addValue;
    if(numToAdd < 0)
    {
        //cout << "Cannot add negative number to a pot." << endl;
    }
    else
        potValue = potValue + numToAdd;
}

int blackjackPot::getValue(){
    return potValue;
}

void blackjackPot::clearPot(){
    potValue = 0;
}
