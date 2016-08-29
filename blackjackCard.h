#ifndef BLACKJACKCARD_H
#define BLACKJACKCARD_H

#include <stdio.h>
#include <string>

/*Andy Yee (24499586)
*Project 1
*ECE 373
*/

/*DOCUMENT REVISION
10/14/11 - (v0.01) Creation of card.h
10/19/11 - (v0.10) Revised functions such that only newCard() is required to draw a card.
				   Implemented an abstract card library; declared in card.cpp .
				   Implementation of a card structure.
10/20/11 - (v1.00) Removed card library and card structure.
                   Re-implemented constructor header.
	   (v1.01) Included empty constructor method.
*/
using namespace std;

class blackjackCard{ // class definition
public:
	string face;
	string suit;
	int value;

    blackjackCard();
    blackjackCard(int cardRef);
};
#endif
