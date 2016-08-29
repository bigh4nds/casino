//#include "BattleCards.cpp"
#ifndef BATTLECAREDS_H
#define BATTLECARDS_H
#include <iostream>
#include <string>
using namespace std;
/* BattleCards class contains the methods needed to create the computer and player decks
* The class  is implemented with a circular queue and includes case statements that check
* for the capacity of the queue's.
*/

//Class Definition
class BattleCards
{

        public :
                BattleCards(void);//make an array with arbitrary elements
                void addCard(int card,string user); //adds to queue
                void displayDeck(string user);//displays queue
                int removeCard(string user);
		void pickUp(string user);
		int isPlayerEmpty();
		int isComputerEmpty();
		int computerDeckSize();
		int playerDeckSize();
		int playedCardsSize();
        private :
                int *playerDeck,*computerDeck, *playedCards;
                int front, rear, cfront, crear;
                int MAX, cMAX, playerDeckCount, computerDeckCount, head, tail;
};
#endif


