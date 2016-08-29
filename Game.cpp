#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Game.h"
#include <string>


#ifndef BATTLECARDS_H
	#define BATTLECARDS_H
	#include "BattleCards.h"
#endif
#ifndef WARDISPLAY_H
	#define WARDISPLAY_H
	#include "WarDisplay.h"
#endif
#ifndef Display_H
	#define Display_H
	#include "display.h"
#endif	
#include "Umbrella_Class.h"


using namespace std;
int* cardVals;
Umbrella_Class *warStats;
Game::Game(Umbrella_Class * ptr){
	warStats=ptr;
}

Game::~Game(void){
                //pritnout the destruction statement
        cout<< "The Game has been destroyed." << endl;
        }

//////////////////////////////Computer Class/////////////////////////

int Game::computerShoot(){
        computerCardVal = battlecard.removeCard("computer");
        wardisplay.displayComputersCardFaceDown(computerCardVal);
	mvprintw(5, 5, "The computer has %d cards  ", battlecard.computerDeckSize()); 
        mvprintw(17, 5, "There are %d cards currently in play  ", battlecard.playedCardsSize());
        return computerCardVal;
}
void Game::computerPickUp(){
        /*Going to get called from the Winner Class and will look at the
         *current
         *battle stack and place into players hand(look at computer and
         * player played cards
        */
        battlecard.pickUp("computer");
}

//////////////////////////Player Class////////////////////////////////

int Game::playerShoot(){
        playerCardVal = battlecard.removeCard("player");
        wardisplay.displayPlayersCardFaceDown(playerCardVal);
	mvprintw(35, 5, "The player has %d cards  ", battlecard.playerDeckSize());
        warStats->updateCardsPlayed(1);
	return playerCardVal;
}

void Game::playerPickUp(){
        //Going to get called from the Winner Class and will look at the current
        //battle stack and place into players hand(look at computer and player
        //played cards stack
        battlecard.pickUp("player");
}

int * Game::playerFlipCards(){
        playerCardVal = playerShoot();
        computerCardVal = computerShoot();
        //Tell Display class to make "cardVal" visible
	wardisplay.displayPlayersCardFaceUp(playerCardVal);
      	wardisplay.displayComputersCardFaceUp(computerCardVal);
	//mvprintw(1,1,"Player Card=%d  ",playerCardVal);
	//mvprintw(2,1,"Computer Card=%d  ", computerCardVal);
        int playedCards[2]={playerCardVal,computerCardVal};
        pointer=playedCards;
	return pointer;
}


 /////////////////////////////SHUFFLE class//////////////////////////



void Game::shuffleCreateDeck()
{
        srand(time(NULL));
        for(int i = 0; i < DECKSIZE; i++){              //Create Deck In Order
                deck[i] = i;
        }
}

void Game::shuffleDeck()
{
        for(int j = 0; j < DECKSIZE; j++){               //Shuffle Deck
                temp_spot = (rand() % DECKSIZE);
                current_spot = deck[j];
                deck[j] = deck[temp_spot];
                deck[temp_spot] = current_spot;
        }
}

//////////////////////////////DEAL Class////////////////////////////////

void Game::dealCards(){
       
       shuffleCreateDeck();
       shuffleDeck();
        for(int i=0; i<DECKSIZE; i++){
                if( i%2 == 0)
                        battlecard.addCard(deck[i],"player");
                else
                        battlecard.addCard(deck[i],"computer");
        }


}

//////////////////////////////WAR Class///////////////////////////////////


void Game::war(void){
        try{                                                                                                    //error detection
                if(battlecard.computerDeckSize() < 0 || battlecard.computerDeckSize() > 51){        //if the computer's deck is out of bounds
                        throw 1;                                                                                //throw error
                }
	}catch (int e){
		cout << "An exception has occured. Computer deck size out of bounds in War constructor" << endl;
	}
	try{
                if(battlecard.playerDeckSize() < 0 || battlecard.playerDeckSize() > 51){            //if the player's deck is out of bounds
                        throw 1;                                                                                //throw error
                }
        }catch (int e){
                cout << "An exception has occurred. Player deck size out of bounds in War constructor" << endl;
        }
        Game::winnerGame();                                                                            //check if game has ended
        int k = 0;
        while(k < 3){                                                                                           //shoot three cards from each player if possible
		 if(battlecard.playerDeckSize() > 1){                                                  //if there is more than 1 card left in the player's deck
                        playerShoot();                                                                        //shoot a card
                }
		if(battlecard.computerDeckSize() > 1){                           			//if there is more than 1 card left in the computer's deck
                        computerShoot();                                                                      //shoot a card
		}      
                k++;
        }//end of while
                                                                                                                //if they are the same, war is called again through winnerHand
}//end of war method


///////////////////////////////////////Winner Class//////////////////////////////////

/*The winnerHand method says who won the hand and if
*  it is a tie, enters a war
*
*  if the computer's card is larger, 1 is returned
*  if the player's card is larger, 0 is returned
*  if the cards are the same, return NULL
*/

int Game::winnerHand(int y, int x){
   int compCard = x;
   int playerCard = y;
   compCard = compCard % 13;
   playerCard = playerCard % 13;

   if(compCard == 0){
	compCard = 13;
   }
   if(playerCard == 0){
	playerCard = 13;
   }	

   if(compCard > playerCard){                           //if the computer's card value is higher return 1
        winnerGame();					//check to see if the game is over
	//wardisplay.bannerTop("The Computer wins this battle!");					
        return 1;
        }
   else if(playerCard > compCard){                      //if the player's card value is higher return 0
        winnerGame();					//check to see if the game is over
	//wardisplay.bannerTop("The Player wins this battle!");
        return 0;
   }
   else if(playerCard == compCard){                     //if the values are the same enter war
        //wardisplay.bannerTop("WAR!!!!!!!!!!!!");
	//Mul++;	//used to shift playedCards
	war();
	return 2;
				                           //check to see if the game is over
   }
   return 3;
}//end of winnerHand method

/*the winnerGame method says if the game is over who wins
*  return of 2 means player wins
*  return of 1 means computer wins
*  return of 0 means the game should continue
*/


int Game::winnerGame(){
   if(battlecard.computerDeckSize() == 0 && battlecard.playerDeckSize() != 0){              //check to see if the computer's deck is empty
        return 2;                                                                                       //return 2 if the computer's deck is empty
   }
   else if(battlecard.playerDeckSize() == 0 && battlecard.computerDeckSize() !=0){          //check to see if the player's deck is empty
        return 1;                                                                                       //return 1 if the player's deck is empty
   }
   else{
        return 0;                                                                                       //if neither deck is empty return a 0
   }
}

