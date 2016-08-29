//#include "BattleCards.cpp"
#ifndef MainWar_H
	#define MainWar_H
#include <iostream>
#include <string>
//#ifndef Umbrella_H
//#define Umbrella_H
#include "Umbrella_Class.h"
using namespace std;
/* BattleCards class contains the methods needed to create the computer and player decks
* The class  is implemented with a circular queue and includes case statements that check
* for the capacity of the queue's.
*/

//Class Definition
class main_war
{

        public :
                main_war(void);//make an array with arbitrary elements
		~main_war(void);
		int	runWar(Umbrella_Class * umb);
        private :
};
#endif

