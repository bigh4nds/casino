/* Derek Thrasher 2011 ECE373
 * Integrated Umbrella Class
 * Filename: Umbrella_Class.cpp
 *
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include "Umbrella_Class.h"
using namespace std;
#ifndef Display_H
        #define Display_H
        #include "display.h"
#endif


/*
THINGS YOU NEED TO DO
*take your main method that is used to run your game and create a function that takes in the parameter (Umbrella_Class *umbrella)
*place the startTimer(); at the beginning of your games run function (step that you took previous to this one)
*place the stopTimer(); at the end of the game's function
*next comes updateCardsPlayed(int x); This needs to be place in which ever class deals cards to the player. If you deal cards to the player this function MUST be called with the parameter 
being the number of cards dealt to the player
*Last is updating the balance... I imediately deducted x credits with updateBalance(-X); the second my game started. Onces the player wins the game you then need to call updateBalance(2X);
**
**
*try to follow how I did the pointers if you have any trouble.. Also notice that in my main_war.cpp I had to also pass the Umbrella_Class into my {Game driver(umbrella)}
*
*Good luck
*/



Umbrella_Class::Umbrella_Class(void){
	warTime=0;
	pokerTime=0;
	heartsTime=0;
	baccaratTime=0;
	blackjackTime=0;
	cardsPlayed=0; 
	balance=100;
}
Umbrella_Class::~Umbrella_Class(void){
	//printout the destruction statement
	cout<< "The Umbrella Class has been destroyed"<<endl;
}
void Umbrella_Class::updateTimePlayed(int game, int x){
	switch (game){
		case 0:
			baccaratTime = baccaratTime + x;
                        break;
		case 1:
			blackjackTime = blackjackTime + x;
                        break;
		case 2:
			heartsTime = heartsTime + x;
                        break;
		case 3:
			pokerTime = pokerTime + x;
                        break;
		case 4:
			warTime = warTime + x;
			break;
		default:
			break;
	}
}
void Umbrella_Class::updateCardsPlayed(int x){
	cardsPlayed = cardsPlayed + x;
}
void Umbrella_Class::updateBalance(int balChange){
	balance = balance + balChange;
}
void Umbrella_Class::startTimer(){
	startClock = time(NULL);
}
void Umbrella_Class::stopTimer(int game){
	finishClock = time(NULL);
        int timeCount = (finishClock - startClock);
        updateTimePlayed(game,timeCount);
}
void Umbrella_Class::printCardsPlayed(){
	mvprintw(5,20,"Cards Played: %d",cardsPlayed);
}
void Umbrella_Class::printTimePlayed(){
	mvprintw(10,20,"Time Playing Baccarat = %dm %ds",baccaratTime/60, baccaratTime%60);
        mvprintw(15,20,"Time Playing Black Jack = %dm %ds",blackjackTime/60, blackjackTime%60);
        mvprintw(20,20,"Time Playing Hearts = %dm %ds",heartsTime/60, heartsTime%60);
        mvprintw(25,20,"Time Playing Poker = %dm %ds",pokerTime/60, pokerTime%60);
        mvprintw(30,20,"Time Playing War = %dm %ds",warTime/60,warTime%60);
}
void Umbrella_Class::printBalance(){
	mvprintw(35,20,"Balance = %d", balance);
}
void Umbrella_Class::printStatistics(){
	printCardsPlayed();
	printTimePlayed();
	printBalance();
}
