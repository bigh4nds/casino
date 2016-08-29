#include "BattleCards.h"
#include "WarDisplay.h"
#include <iostream>
#include <string>

using namespace std;

//Class object Definition
//the only paratmeter of the object is to specify the size of the deck being used
BattleCards::BattleCards()
{
	//the size of the deck should be the size of the deck
	MAX = cMAX = 52;
	//make an array the size of a full deck of cards
	playerDeck = new int[MAX];
	computerDeck = new int[cMAX];
	
	playedCards = new int[MAX];
	head=0;
        
	//set the front and rear equal
	front = rear = cfront = crear = -1;
		for( int i = 0; i < MAX; i++ )	
		{
			// make the array full of 0's	
			playerDeck[i] = 52;
			computerDeck[i] = 52;
			playedCards[i] = 52;
		}//for
}


//adds a card to the back  of the deck
void BattleCards::addCard( int card , string user )
{
	if( user == "player")
	{
		if(( rear + 1 ) % MAX == front)
		{
			//cout << "\nPlayers Deck  is full" << endl;
			return;
		}


		//make sure you dont put a card in an array spot that isnt there
		rear = ( rear + 1 ) % MAX;


		//put card on bottom of deck aka value at the final spot in queue
		playerDeck[rear] = card;

		if( front == -1)
			front = 0;
	}//end if
	else if (user == "computer")
	{
	                if(( crear + 1 ) % cMAX == cfront)
                {
                        //cout << "\nComputers Deck is full" << endl;
                        return;
                }


                //make sure you dont put a card in an array spot that isnt there
                crear = ( crear + 1 ) % cMAX;


                //put card on bottom of deck aka value at the final spot in queue
                computerDeck[crear] = card;

                if( cfront == -1)
                        cfront = 0;
	
	}//else if
	else
	{
		cout << " Their are no decks assiciated with this user " << endl;
	}
}
		
//remove a card from the deck
int BattleCards::removeCard(string user){
	if( user == "player")
	{	
		int input;
		if( front == -1 )
		{
			//cout << "\nPlayers Deck is empty" << endl;
			return 0;
		}
	
		//remove card from top of deck
		input = playerDeck[front];
		playerDeck[front] = 52;
		
		//if tail and head are pointing to the same index then set them to their initial positions
		if( front == rear )
		{
			front = -1;
			rear = -1;
		}
		else
		//otherwise increment pointer at the top of the deck to the card below the top
			front = ( front + 1 ) % MAX;
		playedCards[head++]=input;
		return input;
	}//if
	else if (user == "computer")
	{
		     int input;
                //remove card from top of deck
                input = computerDeck[cfront];
                computerDeck[cfront] = 52;
                //if tail and head are pointing to the same index then set them to their initial positions
                if( cfront == crear )
                {
                        cfront = -1;
                        crear = -1;
                }
                else
                //otherwise increment pointer at the top of the deck to the card below the top
                        cfront = ( cfront + 1 ) % cMAX;
                playedCards[head++]=input;
		return input;
	}//end else if
	else
	{
		cout << " There is no user associated with this deck" << endl;
		return 0;
	}//end else
}//end method

void BattleCards::pickUp(string user)
{
	int tail=0;
	while(tail<head){
		if(user == "player"){
			addCard(playedCards[tail++],"player");
		}
		else if (user == "computer"){
			addCard(playedCards[tail++],"computer");
	
		}
	}
	head=0;
}

//displays the contents of the circular array
void BattleCards::displayDeck(string user)
{
	if( user == "player")
	{
		cout << endl;
		for( int i = 0; i < MAX; i++)
			//cout << playerDeck[i] << " ";
		cout << endl;
	}//endif	
	else if ( user == "computer")
	{
		for( int i = 0; i < cMAX; i++)
                	//cout << computerDeck[i] << " ";

                cout << endl;
	
	}//else if 
	else
	{
	//cout << "this works" << endl;
	} //end else
	//Mul=0;	//used to shift played Cards
}

//checks if the computer queue is empty or now
int BattleCards::isComputerEmpty(){
        if(cfront == -1){
                return 0;
        }
	else
		return 1;

}

//checks if the player queue is empty or not
int BattleCards::isPlayerEmpty(){
        if(front == -1){
               return 0;
        }
	else
		return 1;

}
int BattleCards::playedCardsSize(){
        return head;
}

int BattleCards::computerDeckSize(){
	computerDeckCount=0;
	for( int i = 0; i < cMAX; i++){
		if( computerDeck[i] != 52 )
			computerDeckCount++;
	}
	//cout << computerDeckCount << endl;
	return computerDeckCount;
}


int BattleCards::playerDeckSize(){
	playerDeckCount=0;
        for( int i = 0; i < MAX; i++){
                if( playerDeck[i] != 52 )
                        playerDeckCount++;
        }
	//cout << playerDeckCount << endl;
	return playerDeckCount;

}

