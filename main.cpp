#ifndef Display_H
        #define Display_H
        #include "display.h"
#endif
#include "Umbrella_Class.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include "main_war.h"
#include "blackjackMain.h"

using namespace std;

//declare display variable
display GameDisplay;

//resizing of the window
static void detectResize (int sig);

//scans for player's choice in game
int UserPick();

void drawMenu();

Umbrella_Class *umbrella;

//stub for printing the resizing of the window
void stub_PrintResize(void);
//main method
int main(int argc, char* argv[])
{
	Umbrella_Class Umbrella;
	umbrella = &Umbrella;
	main_war War;
	blackjackMain Blackjack;
for(;;){
	signal(SIGWINCH, detectResize); // enable the window resize signal
	drawMenu();
	Umbrella.printStatistics();
		
	int select = 20;


	select = UserPick();

	move(42,60);

	if(select == 0)
		addstr("HEARTS");
	else if(select == 1)
		addstr("POKER");
	else if(select == 2){
		addstr("WAR");
		War.runWar(&Umbrella);
		GameDisplay.drawBox(0,0, 300, 300, 1);
		GameDisplay.eraseBox(0,0,300, 300);
		GameDisplay.drawBox(0,0,300,300,1);
	}
	else if(select == 3)
		addstr("BACCARAT");
	else if(select == 4){
		addstr("BLACKJACK");
		Blackjack.runBlackjack(&Umbrella);
		GameDisplay.drawBox(0, 0, 300, 300, 1);
		GameDisplay.eraseBox(0, 0, 300, 300);
		GameDisplay.drawBox(0, 0, 300, 300, 1);
	}
	else{
		addstr("EXIT");
		exit(0);
	}
}
	return 0;
}

//UserPick definition
int UserPick()
{
	// various variable declarations
	char key;
	int gameX = 0;
	int gameY = 0;

	for (;;) {
		// calls the game display to capture some input
    	key = GameDisplay.captureInput();

		// if a mouse event occurred
		if (key == -1) {

			// check if it was a left click
			if (GameDisplay.getMouseEventButton()&LEFT_CLICK) {

				// record the location of the mouse event
				gameX = GameDisplay.getMouseEventX();
				gameY = GameDisplay.getMouseEventY();

				//uses coordinates to determine index of game
				if(gameX >= 60 && gameX < 90)
				{
					if(gameY >= 10 && gameY < 39)
					{
						if(gameY >= 10 && gameY < 15)
							return 0;
						else if(gameY >= 16 && gameY < 21)
							return 1;
						else if(gameY >= 22 && gameY < 27)
							return 2;
						else if(gameY >= 28 && gameY < 33)
							return 3;
						else
							return 4;

					}

				}

				if(gameX >= 120 && gameX < 140)
				{
					if(gameY >= 40 && gameY < 44)
					{
					  return 5;
					}
				}
		  	 }

		}
	}
}

void detectResize(int sig) {
	// update the display class information with the new window size
    GameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
    signal(SIGWINCH, detectResize);
	/*INSERT YOUR OWN SCREEN UPDATE CODE instead of stub_PrintResize*/
	stub_PrintResize();
}

void stub_PrintResize(void) {
	// gets the new screen size
	int cols = GameDisplay.getCols();
	int lines = GameDisplay.getLines();
	// setups a message stream
	stringstream messageString;
	messageString << "Terminal is " << cols << "x" << lines;
	// prints out the information of the new screen size in a top banner
	GameDisplay.bannerTop(messageString.str());
	drawMenu();
	(*umbrella).printStatistics();
}

void drawMenu() {
	GameDisplay.drawBox(0,0, 300, 300, 1);
	GameDisplay.eraseBox(0,0, 300, 300);
	GameDisplay.drawBox(0,0, 300, 300, 1);
 	GameDisplay.drawBox(60,10,30,5,1);
        move(12,71);
        addstr("HEARTS");
        GameDisplay.drawBox(60,16,30,5,1);
        move(18,72);
        addstr("POKER");
        GameDisplay.drawBox(60,22,30,5,1);
        move(24,73);
        addstr("WAR");
        GameDisplay.drawBox(60,28,30,5,1);
        move(30,71);
        addstr("BACCARAT");
        GameDisplay.drawBox(60,34,30,5,1);
        move(36,70);
        addstr("BLACKJACK");
        GameDisplay.drawBox(120,40,20,4,1);
        move(42,127);
        addstr("EXIT");
}
