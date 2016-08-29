#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <time.h>
//#include <ctime>
#ifndef MainWar_H
        #include "main_war.h"
#endif
#include "Umbrella_Class.h"
#ifndef Game_H
	#define Game_H
	#include "Game.h"
#endif
#ifndef WARDISPLAY_H
	#define WARDISPLAY_H
	#include "WarDisplay.h"
#endif

/*
needed in main.cpp to run War Game

 		addstr("WAR");
                War.runWar(&Umbrella);
                GameDisplay.drawBox(0,0, 300, 300, 1);
                GameDisplay.eraseBox(0,0,300, 300);
                GameDisplay.drawBox(0,0,300,300,1);
*/






// Signal Subroutine for Window Resize
static void detectResizeWar (int sig); 

// stub artifact for what the game does when the screen resizes
void stub_PrintResizeWar(void); 

// The gameDisplay object is global, because the static signal handler object
// needs to access the dynamic object.

display warGameDisplay;


main_war::main_war(){	
}
main_war::~main_war(){
	cout<<"War Game Destroyed"<<endl;
}
int main_war::runWar(Umbrella_Class * umbrella)
{
	
	//statistic handling
	umbrella->startTimer();
	umbrella->printStatistics();
	int charge =3;
	umbrella->updateBalance(-charge);
	


	WarDisplay warDisplay;
	Game driver(umbrella);
	driver.dealCards();

	// using a stringstream rather than a string to make making the banner easier
	stringstream messageString;

	// various variable declarations
	char key;

	// enable a interrupt triggered on a window resize
	signal(SIGWINCH, detectResizeWar); // enable the window resize signal


	// infinite loop for the main program, you can press ctrl-c to quit
	for(;;){
		// calls the game display to capture some input
		key = warGameDisplay.captureInput();
		int gameX = warGameDisplay.getMouseEventX();
		int gameY = warGameDisplay.getMouseEventY();
			// if a mouse event occurred
		if (key == -1) {
                        if (warGameDisplay.getMouseEventButton()&& LEFT_CLICK && gameX>=1 && gameX<=7 && gameY>=1 && gameY<=4  ) {
				break;
			}
			if (warGameDisplay.getMouseEventButton()&& LEFT_CLICK &&gameX>=60 &&gameX<=72 && gameY>=30 && gameY<=39  ) {
		
			/////////////Game Play//////////////
				if(driver.winnerGame() == 0){			
					int* playedCards = driver.playerFlipCards();
					int handWinner = driver.winnerHand(playedCards[0],playedCards[1]);
	         			if(handWinner == 1){
               			        	driver.computerPickUp();
               				}
               				else if(handWinner == 0){
              					 driver.playerPickUp();
               				}
				}//close if
               	        }//close if
        	 } else if(key > 0) {	//if any key was pressed
                	// make bottom a banner message saying that a key was pressed
                	messageString.str("");
                	messageString << "Key " << key << " pressed";
        	       	warGameDisplay.bannerBottom(messageString.str());
          	}



		if(driver.winnerGame() == 2){
 	      	        mvprintw(3,1, "The player won the game");
			if(charge==3){
				umbrella->updateBalance(charge*2);
				charge =0;
			}
       		}
        	if(driver.winnerGame() == 1){
                	mvprintw(3,1, "The computer won the game");
		}

	}
	umbrella->stopTimer(4);
	return 0;
}


void detectResizeWar(int sig) {
        // update the display class information with the new window size
    warGameDisplay.handleResize(sig);
        // re-enable the interrupt for a window resize
    signal(SIGWINCH, detectResizeWar);
        /*INSERT YOUR OWN SCREEN UPDATE CODE instead of 
stub_PrintResize*/
	stub_PrintResizeWar();
}

void stub_PrintResizeWar(void) {
        // gets the new screen size
        int cols = warGameDisplay.getCols();
        int lines = warGameDisplay.getLines();
        // setups a message stream
        stringstream messageString;
        messageString << "Terminal is " << cols << "x" << lines;
        // prints out the information of the new screen size in a top banner
        warGameDisplay.bannerTop(messageString.str());
}

