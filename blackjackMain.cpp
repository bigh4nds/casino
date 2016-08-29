#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <time.h>
#include "blackjackDisplay.h"
#include "blackjackPlayer.h"
#include "blackjackDealer.h"
#include "blackjackDeck.h"
#include "Umbrella_Class.h"
#ifndef BlackjackMain_H
	#include "blackjackMain.h"
#endif
using namespace std;

// GLOBAL OBJECTS
blackjackDisplay gameDisplay;
// Initialize deck
blackjackDeck deck;
// Initialize player
blackjackPlayer player(deck);
// Initialize dealer
blackjackDealer dealer(deck);

// Signal Subroutine for Window Resize
static void detectResize(int sig);
// our own display
void drawDisplay();
// delay method to stall any messages
void wait(int sec);

//GLOBAL GAME VARIABLES
bool falseBet = true;
bool preGame = true;
bool toggleAction = false;
bool promptExit = false;
char actionSel = 'x';


int lines = gameDisplay.getLines();//MADE GLOBAL BY CG SO RESIZE WORKS PROPERLY
int cols = gameDisplay.getCols();

blackjackMain::blackjackMain(){
}

blackjackMain::~blackjackMain(){
	cout<< "Blackjack Game Destroyed" << endl;
}

int blackjackMain::runBlackjack(Umbrella_Class *umbrella) 
{
	// Statistics handling
	umbrella->startTimer();
	umbrella->printStatistics();
	
// using a stringstream rather than a string to make making the banner easier.
	stringstream messageString;
	char key; 
	
	// Mouse listener variables.
	int clickX;
	int clickY;
	//LOCAL VARIABLES
	int bet = 0;
	int betSel = 0;
	char inputSel = 'x';

	// enable an interrupt triggered on a window resize
	signal(SIGWINCH,detectResize); // enable the window resize signal
	
	// Shuffle deck.
	srand(time(NULL));
	deck.shuffleDeck();
	// Initialize player deck.
	player.getDeck(deck);
	// Update the game deck from player.
	deck = player.hand.updateDeckToGame();
	// Initialize dealer deck.
	dealer.getDeck(deck);
	deck = dealer.hand.updateDeckToGame();
	// Update deck to player object
	player.hand.updateDeckToTable(deck);

	drawDisplay();
/*
	messageString.str("");
	messageString << player.hand.card[0].face << " of " << player.hand.card[0].suit;
	gameDisplay.bannerTop(messageString.str());
	messageString << player.hand.card[1].face << " of " << player.hand.card[1].suit;
	gameDisplay.bannerBottom(messageString.str());
	gameDisplay.updateScreen();
	wait(10);
*/
	//------------------------------BEGIN GAME LOOP--------------------------------------------	
	// input loop until user ends the game or user bank goes to zero.	
	while ((inputSel == 'y' || inputSel == 'x' || inputSel != 'n')){
	
		while(player.bank.getTotal() < 100){
			mvprintw(lines/2,cols/2,"%s","Not enough chips");
			wait(3);	
			break;
		}	
	//------------------------------BETTING----------------------------------------------------
		while (falseBet){
			// allows user to select button to place a bet.	
			
			key = gameDisplay.captureInput();
			clickX = gameDisplay.getMouseEventX();
			clickY = gameDisplay.getMouseEventY();
			if(key==-1){//NECESSARY OR ELSE BETTING ROUND IS SKIPPED SINCE INPUTSEL IS ASSUMED 'Y'
			// store coordinates of mouse action.

			// update the display.
			drawDisplay();
			/* Conditional statement: IF user LEFT-CLICKED between a X-RANGE and a Y-RANGE,
			 * then a 'betSel' is selected (for a valid selection).
			 */
			// Select $100.
			if (gameDisplay.getMouseEventButton()==LEFT_CLICK && (clickX >= 2 && 
					clickX <= 12) && (clickY >= lines-6-16 && clickY <= lines-6-16+2)){
				betSel = 1;
				falseBet = false;
			// Select $200.
			} else if (gameDisplay.getMouseEventButton()==LEFT_CLICK &&  
					 (clickX >= 2 && clickX <= 12) &&
						(clickY >= lines-6-12 && clickY <= lines-6-12+2)){ 
				betSel = 2;
				falseBet = false;
			// Select $300.
			} else if (gameDisplay.getMouseEventButton()==LEFT_CLICK && 
					 (clickX >= 2 && clickX <= 12) && 
						(clickY >= lines-6-8 && clickY <= lines-6-8+2)){ 
				betSel = 3;
				falseBet = false;
			// Select $400.
			} else if (gameDisplay.getMouseEventButton()==LEFT_CLICK && 
					 (clickX >= 2 && clickX <= 12) && 
						(clickY >= lines-6-4 && clickY <= lines-6-4+2)){
				betSel = 4;
				falseBet = false;
			// Select $500.
			} else if (gameDisplay.getMouseEventButton()==LEFT_CLICK && 
					 (clickX >= 2 && clickX <= 12) && 
						(clickY >= lines-6 && clickY <= lines-6+2)){
				betSel = 5;
				falseBet = false;
			// Exit game
			} else if(gameDisplay.getMouseEventButton()==LEFT_CLICK &&
					(clickX >= 1 && clickX <= 7) &&
						(clickY >= 1 && clickY <= 4)){
				umbrella->stopTimer(1);
				return 0;
			}

			if (betSel > 0 && betSel <= 5){
				// Interpret into cash.
				switch(betSel){
					case 1: bet = 100; break;
					case 2: bet = 200; break;
					case 3: bet = 300; break;
					case 4: bet = 400; break;
					case 5: bet = 500; break;
					default: bet = 0; break;
				}
				// Check if bet exceeds player's bank total.
				if (bet > player.bank.getTotal()){
					falseBet = true;
					messageString.str("");
					messageString << "Wager exceeds available funds. Bet again:";
					gameDisplay.bannerTop(messageString.str());
					mvprintw(lines/2,cols/2,"%s","Wager exceeds available funds. Bet again:");
					gameDisplay.updateScreen();
					// Stall message for 3 clock ticks.
				//COMMENT BY CGARRY	wait(3); //ADDED BY CGARRY
				} else {
					// Update the player's bank account after betting.
					player.bet(bet);
					// Update screen after bet. This should update bet and erase bet screen.
					drawDisplay();
				}	
			}
 }//ADDED CGARRY END IF KEY==-1
		}//END WHILE(falseBet) 
//------------------------------END BETTING-----------------------------------------------------
		//-------------------------CHECK PLAYER AND DEALER BLACKJACK
		umbrella->updateCardsPlayed(2);
		if (player.hand.getValue() == 21 && dealer.hand.getValue() == 21 && preGame){
			messageString.str("");
			messageString << "Push!";
			gameDisplay.bannerTop(messageString.str());
			player.bank.updateTotal(bet);
			messageString.str("");
			messageString << player.bank.returnTotal();
			gameDisplay.bannerBottom(messageString.str());
			mvprintw(lines/2,cols/2,"%s","Push!");
			gameDisplay.updateScreen();
			wait(3);
			toggleAction = false;
			promptExit = true;
			drawDisplay();
		}//------------------------END CHECK PLAYER AND DEALER BLACKJACK
		//-------------------------CHECK DEALER BLACKJACK
		else if (dealer.hand.getValue() == 21 && preGame){
			messageString.str("");
			messageString << "Dealer has Blackjack.";
			gameDisplay.bannerTop(messageString.str());
			mvprintw(lines/2,cols/2,"%s","Dealer has BlackJack.");
			gameDisplay.updateScreen();
			umbrella->updateBalance(-1);
			wait(3);
			toggleAction = false;
			promptExit = true;
			drawDisplay();
		}//-----------------------END CHECK DEALER BLACKJACK
		//------------------------CHECK PLAYER BLACKJACK
		else if (player.hand.getValue() == 21 && preGame){
			messageString.str("");
			messageString << "Player has Blackjack!";
			gameDisplay.bannerTop(messageString.str());
			player.bank.updateTotal(2*bet);//ADDED BY CGARRY	
			mvprintw(lines/2,cols/2,"%s","Player has BlackJack!");
			umbrella->updateBalance(2);
			gameDisplay.updateScreen();
			wait(3);
			toggleAction = false;
			promptExit = true;
			drawDisplay();
		}//-----------------------END CHECK PLAYER BLACKJACK
//****************************NON-BLACKJACK SCENARIOS******************************************
		else{
			preGame = false;
			///////////////////////////////////CHANGE THIS BELOW///////////////////
			toggleAction = true;
			//////////////////////////////////////////////////////////////////////
			while (actionSel == 'h' || actionSel == 'x'){
				drawDisplay();
				key = gameDisplay.captureInput();
				// store coordinates of mouse action.
				clickX = gameDisplay.getMouseEventX();
				clickY = gameDisplay.getMouseEventY();
				if (key == -1){
					// Select Hit
					if ((clickX >= 2 && clickX <= 12) &&
							((clickY >= lines-6 && clickY <= lines-6+2))){ 
						player.hit();
						umbrella->updateCardsPlayed(1);
						// Update the display everytime a card is hit.
						drawDisplay();
						deck = player.hand.updateDeckToGame();
						dealer.hand.updateDeckToTable(deck);
						// Check for bust.
						if (player.hand.getValue() > 21)
							actionSel = 's';
						else
							actionSel = 'h';
					// Select Stand
					} else if ((clickX >= 2 && clickX <= 12) &&
							(clickY >= lines-6-4 && clickY <= lines-6-4+2)){
						player.stand();
						actionSel = 's';
						break;
					// Select Surrender
					} else if ((clickX >= 2 && clickX <= 12) &&
							(clickY >= lines-6-8 && clickY <= lines-6-8+2)){
						if(player.hand.numCards == 2){
							player.surrender();
							actionSel = 'u';
							player.bank.updateTotal(bet/2);	
							mvprintw(lines/2,cols/2,"%s","Player surrenders");			
							gameDisplay.updateScreen();	
							wait(3);
							// Reset bet.
							bet = 0;
							drawDisplay();
						} else {
							messageString.str("");
							messageString << "Error: Cannot surrender after first turn";
							gameDisplay.bannerTop(messageString.str());
							actionSel = 'x';//CHANGED FROM 'r' TO 'x'
							mvprintw(lines/2,(cols/2)-6,"%s","Cannot surrender after first turn");
							gameDisplay.updateScreen();
							wait(3);
							drawDisplay();	
						}// END PROMPT USER
					} else if ((clickX >= 1 && clickX <= 7) &&
							(clickY >= 1 && clickY <= 4)){
								umbrella->stopTimer(1);
								return 0;
							}
							 
				}//END IF MOUSE ACTION.
			}//END WHILE
			
			// Print message if player BUST.
			if (player.hand.getValue() > 21){
				messageString.str("");
				messageString << "Player Bust!";
				gameDisplay.bannerTop(messageString.str());
				mvprintw(lines/2,cols/2,"%s","Player Bust!");
				umbrella->updateBalance(-1);
				gameDisplay.updateScreen();
		                wait(3);
			        promptExit = true;//ADDED BY CGARRY
				drawDisplay();	
			}//--------------------END IF PLAYER BUSTS
			//---------------------IF PLAYER DID NOT SURRENDER AND IS DONE HITTING OR BUSTS----
			else if (actionSel == 's'){
				dealer.hand.updateDeckToTable(deck);
				//DEALER KEEPS HITTING HERE-----------
				dealer.playHand();
				drawDisplay();
				//END PRINT DEALER HAND
				switch(dealer.getStatus()){
					// Dealer bust.
					case(0):
						messageString.str("");
						messageString << "Player wins!";//ADDED CG
						player.bank.updateTotal(2*bet);	
						umbrella->updateBalance(1);
						gameDisplay.bannerTop(messageString.str());
				         	mvprintw(lines/2,cols/2,"%s","Dealer Busts. Player Wins!");
						gameDisplay.updateScreen();
						wait(3);
						bet = 0;
						drawDisplay();
						break;
					// Dealer gets 21.
					case(1):
						messageString.str("");
						messageString << "Dealer has 21. Dealer wins.";
						gameDisplay.bannerTop(messageString.str());
				        	mvprintw(lines/2,cols/2,"%s","Dealer has 21. Dealer Wins");
						umbrella->updateBalance(-1);
						gameDisplay.updateScreen();
						wait(3);
						bet = 0;
						drawDisplay();
						break;
					// Dealer stays. Compare Player's and Dealer's hand.
					case(2):
						// If player's hand is greater than that of the dealer, player wins.
						if (player.hand.getValue() > dealer.hand.getValue()){
							player.bank.updateTotal(2*bet);
							umbrella->updateBalance(1);
							messageString.str("");
							messageString << "Player wins!";//ADDED CG
							gameDisplay.bannerTop(messageString.str());
							mvprintw(lines/2,cols/2,"%s","Player Wins!");
							gameDisplay.updateScreen();
							wait(3);
							drawDisplay();
						}
						// If player's hand is less than that of the dealer, player loses.
						else if (player.hand.getValue() < dealer.hand.getValue()){
							messageString.str("");
							messageString << "Dealer wins.";//ADDED CG
							gameDisplay.bannerTop(messageString.str());
							mvprintw(lines/2,cols/2,"%s","Dealer Wins");
							umbrella->updateBalance(-1);
							gameDisplay.updateScreen();
							wait(3);
							drawDisplay();
						}
						// If player's hand is equal to the dealer, there is a tie.
						else if (player.hand.getValue() == dealer.hand.getValue()){
							player.bank.updateTotal(bet);	
							messageString.str("");
							messageString << "Push!";
							gameDisplay.bannerTop(messageString.str());
							mvprintw(lines/2,cols/2,"%s","Push!");	
							gameDisplay.updateScreen();
							wait(3);
							drawDisplay();
						}
						bet = 0;
						break;
				}//END SWITCH DEALER STATUS
				toggleAction = false;
				promptExit = true;
				drawDisplay();
			}//END ELSE IF(actionSel == 's')
			else if (actionSel == 'u'){
				toggleAction = false;
				promptExit = true;
				drawDisplay();
			}
		//**************************END DEALER ACTIONS*****************************************
		//--------------------------END IF PLAYER DID NOT SURRENDER AND IS DONE HITTING--------
		}//END ELSE

		// ASSUME PLAYER WANTS TO PLAY AGAIN	
			
			inputSel = 'y';
			blackjackDeck deck;
			srand(time(NULL));
			deck.shuffleDeck();
			player.newHand(deck);
			deck = player.hand.updateDeckToGame();
			dealer.newHand(deck);
			deck = dealer.hand.updateDeckToGame();
			player.hand.updateDeckToTable(deck);
			actionSel = 'x';
			betSel = 0;
			promptExit = false;
			toggleAction = false;
			falseBet = true;
			preGame = true;
			drawDisplay();
			
	}//END GAME WHILE LOOP
	umbrella->stopTimer(1);
	return 0;
}//END MAIN()

/*
 * This is the interrupt service routine called when the resize screen
 * signal is captured.
 */
void detectResize(int sig){
	// update the display class information with the new window size
	gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
	signal(SIGWINCH, detectResize);
	drawDisplay();
}

void drawDisplay(){
	cols = gameDisplay.getCols();//MADE SO THAT COLS AND LINES ARE GLOBALLY ACCESSIBLE BY CGARRY
	lines = gameDisplay.getLines();
	int suitNum = 0;
	int faceNum = 0;

	stringstream messageString;
	
	//////////////////////////////////////////////////////////////
	// Clear display
	gameDisplay.drawBox(0,0,cols,lines,0);
	gameDisplay.eraseBox(0,0,cols,lines);
	//////////////////////////////////////////////////////////////
	// Draw an outline.
	gameDisplay.drawBox(0, 1, cols, lines, 0);
	gameDisplay.drawBox(2, 2, 6, 3, 1);
	mvprintw(3, 3, "EXIT");
	// Display bank total.	
	messageString.str("");
	messageString << "Bank Total: " << player.bank.returnTotal();
	gameDisplay.bannerBottom(messageString.str());

	// Display player's hands.
	for (int i = 0; i < player.hand.numCards; i++){
		/*messageString.str("");
		messageString << player.hand.card[0].face << " of " << player.hand.card[0].suit;
		gameDisplay.updateScreen();
		wait(1);
		gameDisplay.bannerBottom(messageString.str());*/
		// Need to convert the suit from string to int.
		if ((player.hand.card[i].suit).compare("Spades") == 0){
			suitNum = 1;
		} else if ((player.hand.card[i].suit).compare("Hearts") == 0){
			suitNum = 2;
		} else if ((player.hand.card[i].suit).compare("Clubs") == 0){
			suitNum = 3;
		} else if ((player.hand.card[i].suit).compare("Diamonds") == 0){
			suitNum = 4;
		}
		// Need to convert the face from string to int.
		if ((player.hand.card[i].face).compare("Ace") == 0){
			faceNum = 1;
		} else if ((player.hand.card[i].face).compare("Two") == 0){
			faceNum = 2;
		} else if ((player.hand.card[i].face).compare("Three") == 0){
			faceNum = 3;
		} else if ((player.hand.card[i].face).compare("Four") == 0){
			faceNum = 4;
		} else if ((player.hand.card[i].face).compare("Five") == 0){
			faceNum = 5;
		} else if ((player.hand.card[i].face).compare("Six") == 0){
			faceNum = 6;
		} else if ((player.hand.card[i].face).compare("Seven") == 0){
			faceNum = 7;
		} else if ((player.hand.card[i].face).compare("Eight") == 0){
			faceNum = 8;
		} else if ((player.hand.card[i].face).compare("Nine") == 0){
			faceNum = 9;
		} else if ((player.hand.card[i].face).compare("Ten") == 0){
			faceNum = 10;
		} else if ((player.hand.card[i].face).compare("Jack") == 0){
			faceNum = 11;
		} else if ((player.hand.card[i].face).compare("Queen") == 0){
			faceNum = 12;
		} else if ((player.hand.card[i].face).compare("King") == 0){
			faceNum = 13;
		}

		// Prints out card in hand.
		gameDisplay.displayCard((cols/2)+(i*6)-5,(int)lines-8,
			suitNum,faceNum, A_BOLD);
	}
	
	for (int j = 0; j < dealer.hand.numCards; j++){
		// Convert suit from string to int.
		if ((dealer.hand.card[j].suit).compare("Spades") == 0){
			suitNum = 1;
		} else if ((dealer.hand.card[j].suit).compare("Hearts") == 0){
			suitNum = 2;
		} else if ((dealer.hand.card[j].suit).compare("Clubs") == 0){
			suitNum = 3;
		} else if ((dealer.hand.card[j].suit).compare("Diamonds") == 0){
			suitNum = 4;
		}
		// Convert face from string to int.
		if ((dealer.hand.card[j].face).compare("Ace") == 0){
			faceNum = 1;
		} else if ((dealer.hand.card[j].face).compare("Two") == 0){
			faceNum = 2;
		} else if ((dealer.hand.card[j].face).compare("Three") == 0){
			faceNum = 3;
		} else if ((dealer.hand.card[j].face).compare("Four") == 0){
			faceNum = 4;
		} else if ((dealer.hand.card[j].face).compare("Five") == 0){
			faceNum = 5;
		} else if ((dealer.hand.card[j].face).compare("Six") == 0){
			faceNum = 6;
		} else if ((dealer.hand.card[j].face).compare("Seven") == 0){
			faceNum = 7;
		} else if ((dealer.hand.card[j].face).compare("Eight") == 0){
			faceNum = 8;
		} else if ((dealer.hand.card[j].face).compare("Nine") == 0){
			faceNum = 9;
		} else if ((dealer.hand.card[j].face).compare("Ten") == 0){
			faceNum = 10;
		} else if ((dealer.hand.card[j].face).compare("Jack") == 0){
			faceNum = 11;
		} else if ((dealer.hand.card[j].face).compare("Queen") == 0){
			faceNum = 12;
		} else if ((dealer.hand.card[j].face).compare("King") == 0){
			faceNum = 13;
		}
		// Prints out dealer's cards in hand.
		if (dealer.hand.numCards == 2 && j == 0 && dealer.hand.getValue() != 21
				&& actionSel != 's')
			gameDisplay.displayCard((cols/2)+(j*6)-5,3,-1,-1,A_BOLD);
		else
			gameDisplay.displayCard((cols/2)+(j*6)-5,3,suitNum,faceNum, A_BOLD);
	}

	// Deck aesthetics.	
	gameDisplay.displayCard(cols-10,(int)lines/2,0,0, A_BOLD);
	gameDisplay.displayCard(cols-9,(int)lines/2,0,0, A_BOLD);
	gameDisplay.displayCard(cols-8,(int)lines/2,0,0, A_BOLD);

	// BETTING STAGE.	
	if (falseBet && !toggleAction){
		// Banner message to prompt user input to bet an amount.
		messageString.str("");
		messageString << "Please click on a bet amount";
		gameDisplay.bannerTop(messageString.str());
		// Mask display (of cards)
		gameDisplay.drawBox(0,1,cols,lines-2,0);
		gameDisplay.eraseBox(0,1,cols,lines-2);
		gameDisplay.drawBox(2,2,6,3,1);
		mvprintw(3,3,"EXIT");
		//=================== $100 =============================
		// Draw a box.
		gameDisplay.drawBox(2,lines-6-16,10,3,0);
		// Print text $100. Coordinates are REVERSED (Y,X,type,string);
		mvprintw(lines-21,cols-(cols-5),"%s","$100");
		//======================================================
		//=================== $200 =============================
		// Draw a box.
		gameDisplay.drawBox(2,lines-6-12,10,3,0);
		// Print text $200.
		mvprintw(lines-17,5,"%s","$200");
		//======================================================
		//=================== $300 =============================
		// Draw a box.
		gameDisplay.drawBox(2,lines-6-8,10,3,0);
		// Print text $300.
		mvprintw(lines-13,cols-(cols-5),"%s","$300");
		//======================================================
		//=================== $400 =============================
		// Draw a box.
		gameDisplay.drawBox(2,lines-6-4,10,3,0);
		// Print text $400.
		mvprintw(lines-9,cols-(cols-5),"%s","$400");
		//=================== $500 =============================
		// Draw a box.
		gameDisplay.drawBox(2,lines-6,10,3,0);
		// Print text $500.
		mvprintw(lines-5,5,"%s","$500");
		mvprintw(lines/2,cols/2,"%s","Please click on a bet amount");

	// ACTION STAGE (HIT, STAND, or SURRENDER)
	} else if (!falseBet && toggleAction){
		messageString.str("");
		messageString << "Please click an option";
		gameDisplay.bannerTop(messageString.str());
		/////////////////////////////////////////////////////////
		// Clear bet screen display.
		gameDisplay.drawBox(2,lines-6-8,10,12,0);
		gameDisplay.eraseBox(2,lines-6-8,10,12);
		/////////////////////////////////////////////////////////
		//=================== HIT ===============================
		gameDisplay.drawBox(2,lines-6,10,3,0);	
		mvprintw(lines-5,cols-(cols-6),"%s","HIT");
		//=======================================================
		//=================== STAND =============================
		gameDisplay.drawBox(2,lines-6-4,10,3,0);
		mvprintw(lines-9,cols-(cols-5),"%s","STAND");
		//=======================================================
		//=================== SURRENDER =========================
		gameDisplay.drawBox(2,lines-6-8,10,3,0);
		mvprintw(lines-13,cols-(cols-5),"%s","SURR");

	//=======================================================
	// REPLAGE STAGE (EXIT or PLAY AGAIN)
	 } 
	
/*
	messageString.str("");
	messageString << "Mouse event occurred x=" \
		<< gameDisplay.getMouseEventX() << ", y=" \
		<< gameDisplay.getMouseEventY() << ", bstate=" \
		<< gameDisplay.getMouseEventButton();
	gameDisplay.bannerTop(messageString.str());*/
//	messageString.str("");
//	messageString << "Window size: " << cols << " by " << lines;
//	gameDisplay.bannerBottom(messageString.str());
	gameDisplay.updateScreen();
}
// Delay method.
// Resource: new.cplusplus.com/reference/clibrary/ctime/clock
void wait (int sec){
	clock_t endwait;
	endwait = clock() + sec * CLOCKS_PER_SEC;
	while (clock() < endwait){}
}
