#include <stdio.h>
#include <string.h>
#include "blackjackCard.h"

/*Andy Yee (24499586)
*Project 1
*ECE 373
*/

/*DOCUMENT REVISION
10/12/11 - (v0.01) Creation of card.cpp
10/14/11 - (v0.15) Changed displayCard() to create stringstream instead of print line in method.
                   Split card.cpp into a header, "card.h"
                   Implementation of a non-working driver.
10/19/11 - (v0.20) Changed argument type in getFace() & getSuit() in order to be consistent with the initial UML class diagram.
                   Created a struct and enum for card library.
                   TODO: Implement Ace cards of value 1 or 11.
10/20/11 - (v0.30) Removed stringstream and printed string in displayCard().
				   Reclassified older implemented functions as stubs.
           (v1.00) Removed struct and enum due to incorrect implementation.
                   Removed getFace(), getSuit(), and getValue() due to redundancy.
                   Constructor contains a integer parameter.
                   Changed value of Ace cards to 11 by default.
	   (v1.01) Included empty constructor, required for the Deck Class.
*/
blackjackCard::blackjackCard(){}
blackjackCard::blackjackCard(int cardRef){
    // Determines a card based on cardRef paramemeter.
    switch (cardRef){
		case 0: //AceOfClubs
			face = "Ace";
			suit = "Clubs";
			value = 11;
			break;
		case 1: //TwoOfClubs
			face = "Two";
			suit = "Clubs";
			value = 2;
			break;
		case 2: //ThreeOfClubs
			face = "Three";
			suit = "Clubs";
			value = 3;
			break;
		case 3: //FourOfClubs
			face = "Four";
			suit = "Clubs";
			value = 4;
			break;
		case 4: //FiveOfClubs
			face = "Five";
			suit = "Clubs";
			value = 5;
			break;
		case 5: //SixOfClubs
			face = "Six";
			suit = "Clubs";
			value = 6;
			break;
		case 6: //SevenOfClubs
			face = "Seven";
			suit = "Clubs";
			value = 7;
			break;
		case 7: //EightOfClubs
			face = "Eight";
			suit = "Clubs";
			value = 8;
			break;
		case 8: //NineOfClubs
			face = "Nine";
			suit = "Clubs";
			value = 9;
			break;
		case 9: //TenOfClubs
			face = "Ten";
			suit = "Clubs";
			value = 10;
			break;
		case 10: //JackOfClubs
			face = "Jack";
			suit = "Clubs";
			value = 10;
			break;
		case 11: //QueenOfClubs
			face = "Queen";
			suit = "Clubs";
			value = 10;
			break;
		case 12: //KingOfClubs
			face = "King";
			suit = "Clubs";
			value = 10;
			break;
		case 13: //AceOfDiamonds
			face = "Ace";
			suit = "Diamonds";
			value = 11;
			break;
		case 14: //TwoOfDiamonds
			face = "Two";
			suit = "Diamonds";
			value = 2;
			break;
		case 15: //ThreeOfDiamonds
			face = "Three";
			suit = "Diamonds";
			value = 3;
			break;
		case 16: //FourOfDiamonds
			face = "Four";
			suit = "Diamonds";
			value = 4;
			break;
		case 17: //FiveOfDiamonds
			face = "Five";
			suit = "Diamonds";
			value = 5;
			break;
		case 18: //SixOfDiamonds
			face = "Six";
			suit = "Diamonds";
			value = 6;
			break;
		case 19: //SevenOfDiamonds
			face = "Seven";
			suit = "Diamonds";
			value = 7;
			break;
		case 20: //EightOfDiamonds
			face = "Eight";
			suit = "Diamonds";
			value = 8;
			break;
		case 21: //NineOfDiamonds
			face = "Nine";
			suit = "Diamonds";
			value = 9;
			break;
		case 22: //TenOfDiamonds
			face = "Ten";
			suit = "Diamonds";
			value = 10;
			break;
		case 23: //JackOfDiamonds
			face = "Jack";
			suit = "Diamonds";
			value = 10;
			break;
		case 24: //QueenOfDiamonds
			face = "Queen";
			suit = "Diamonds";
			value = 10;
			break;
		case 25: //KingOfDiamonds
			face = "King";
			suit = "Diamonds";
			value = 10;
			break;
		case 26: //AceOfSpades
			face = "Ace";
			suit = "Spades";
			value = 11;
			break;
		case 27: //TwoOfSpades
			face = "Two";
			suit = "Spades";
			value = 2;
			break;
		case 28: //ThreeOfSpades
			face = "Three";
			suit = "Spades";
			value = 3;
			break;
		case 29: //FourOfSpades
			face = "Four";
			suit = "Spades";
			value = 4;
			break;
		case 30: //FiveOfSpades
			face = "Five";
			suit = "Spades";
			value = 5;
			break;
		case 31: //SixOfSpades
			face = "Six";
			suit = "Spades";
			value = 6;
			break;
		case 32: //SevenOfSpades
			face = "Seven";
			suit = "Spades";
			value = 7;
			break;
		case 33: //EightOfSpades
			face = "Eight";
			suit = "Spades";
			value = 8;
			break;
		case 34: //NineOfSpades
			face = "Nine";
			suit = "Spades";
			value = 9;
			break;
		case 35: //TenOfSpades
			face = "Ten";
			suit = "Spades";
			value = 10;
			break;
		case 36: //JackOfSpades
			face = "Jack";
			suit = "Spades";
			value = 10;
			break;
		case 37: //QueenOfSpades
			face = "Queen";
			suit = "Spades";
			value = 10;
			break;
		case 38: //KingOfSpades
			face = "King";
			suit = "Spades";
			value = 10;
			break;
 	        case 39: //AceOfHearts
			face = "Ace";
			suit = "Hearts";
			value = 11;
			break;
       	 	case 40: //TwoOfHearts
			face = "Two";
			suit = "Hearts";
			value = 2;
			break;
		case 41: //ThreeOfHearts
			face = "Three";
			suit = "Hearts";
			value = 3;
			break;
		case 42: //FourOfHearts
			face = "Four";
			suit = "Hearts";
			value = 4;
			break;
		case 43: //FiveOfHearts
			face = "Five";
			suit = "Hearts";
			value = 5;
			break;
		case 44: //SixOfHearts
			face = "Six";
			suit = "Hearts";
			value = 6;
			break;
		case 45: //SevenOfHearts
			face = "Seven";
			suit = "Hearts";
			value = 7;
			break;
		case 46: //EightOfHearts
			face = "Eight";
			suit = "Hearts";
			value = 8;
			break;
		case 47: //NineOfHearts
			face = "Nine";
			suit = "Hearts";
			value = 9;
			break;
		case 48: //TenOfHearts
			face = "Ten";
			suit = "Hearts";
			value = 10;
			break;
		case 49: //JackOfHearts
			face = "Jack";
			suit = "Hearts";
			value = 10;
			break;
		case 50: //QueenOfHearts
			face = "Queen";
			suit = "Hearts";
			value = 10;
			break;
		case 51: //KingOfHearts
			face = "King";
			suit = "Hearts";
			value = 10;
			break;
        default: // Out of Bounds
            face = "NaN";
            suit = "NaN";
            value = 9000;
            break;
	}
}
