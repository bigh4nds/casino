//warDisplay.h


#ifndef WARDISPALY_H
#define WARDISPLAY_H
#ifndef Display_H
	#define Display_H
	#include "display.h"
#endif


using namespace std;

class WarDisplay {

public:
       	WarDisplay(void);//constructor
        
           
	display gameDisplay;
		 
	 void displayPlayersCardFaceUp(int playersCard);
	 void displayComputersCardFaceUp(int computersCard);
	 void displayPlayersCardFaceDown(int playersCard);
	 void displayComputersCardFaceDown(int computersCard);
	int Mul;
private:
	int xPos;
	int yPos;
	int xOffset;
	int yOffset;


};

#endif
