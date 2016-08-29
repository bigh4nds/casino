/* Derek Thrasher 2011 ECE373
 * Integrated Umbrella Class
 * Filename: Umbrella_Class.h
 *
 */
#ifndef Umbrella_H
#define Umbrella_H
class Umbrella_Class {
        public:
                Umbrella_Class(void);
                ~Umbrella_Class(void);
	void	updateTimePlayed(int game, int x);
	void	updateCardsPlayed(int x);
	void 	updateBalance(int x);	
        void 	startTimer();
	void 	stopTimer(int game);
	void 	printCardsPlayed();
	void 	printTimePlayed();
	void	printBalance();
	void	printStatistics();
	int     warTime, pokerTime, heartsTime, baccaratTime, blackjackTime; 
	int	cardsPlayed;
	int	balance;
	int 	startClock, finishClock, timeCount; 
        private:
        //
};

#endif
