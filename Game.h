#ifndef GAME_H
#define GAME_H

#define DECKSIZE 52

#include "BattleCards.h"
#include "WarDisplay.h"
#include "Umbrella_Class.h"



class Game {
        public:
                Game(Umbrella_Class *umb);
                ~Game(void);

	BattleCards battlecard;	
	WarDisplay wardisplay;

        int*    playerFlipCards();
        int     playerShoot();
        void    playerPickUp();
        int     playerCardVal;
        int     playedCards[];
        int*    pointer;

        int     computerShoot();
        void    computerPickUp();
        int     computerCardVal;

	void	shuffleCreateDeck();
	void	shuffleDeck();
	int	deck[DECKSIZE];
	int	temp_spot, current_spot;

        void    dealCards();


	void war(void);


        int winnerHand(int x, int y);
        int winnerGame();






        private:
        //


};

#endif
