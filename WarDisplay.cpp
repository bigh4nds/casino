#ifndef WarDisplay_H
	#define WarDisplay_H
	#include "WarDisplay.h"
#endif
#include <iostream>

#ifndef Display_H
	#define Display_H
	#include "display.h"
#endif


WarDisplay::WarDisplay(void){
	gameDisplay.drawBox(0,0,80,40,1);
	gameDisplay.drawBox(1,1,6,3,1);
	mvprintw(2,2,"EXIT");
	gameDisplay.drawBox(60,30,12,9,1);
	mvprintw(34,62,"Flip Card");
	xPos=0;
	yPos=0;
	xOffset=1;
	yOffset=1;
	Mul=0;
	mvprintw(15,30,"Computer's Hand");
	mvprintw(18,30,"Player's Hand");	
}

//This method will display players card face up 
void WarDisplay::displayPlayersCardFaceUp(int playersCard) {
	//std::cout << "you are getting in the functions " << std::endl;
	int suit = playersCard/13 + 1;//determins the proper suit based on  Dispay.cpp's cases
	int number = playersCard%13 + 1;//determines the proper card number based on Display.cpp's cases

		
	 gameDisplay.displayCard(30+xOffset*Mul,20+yOffset*Mul,suit,number, A_BOLD);
	
}



//This method will display computers card face up
void WarDisplay::displayComputersCardFaceUp(int computersCard) {
	

	//std::cout << "you are getting in the functions " << std::endl;

        int suit = computersCard/13 + 1;//determins the proper suit based on  Dispay.cpp's cases
        int number = computersCard%13 + 1;//determines the proper card number based on Display.cpp
 	
	gameDisplay.displayCard(30-(xOffset*Mul),10-(yOffset*Mul),suit,number, A_BOLD);


}
//displays the a card face down from the players deck
void WarDisplay::displayPlayersCardFaceDown(int playersCard){
	gameDisplay.displayCard(30+(xOffset*Mul),20+(yOffset*Mul),0,0, A_BOLD);
}

//displays a computer card facedown from the deck
void WarDisplay::displayComputersCardFaceDown(int computersCard){
	 gameDisplay.displayCard(30-(xOffset*Mul),10-(yOffset*Mul),0,0, A_BOLD);
}




