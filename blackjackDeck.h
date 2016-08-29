#ifndef BLACKJACKDECK_H                  //Guard to determine if deck.h has already been included to avoid multiple definition errors
#define BLACKJACKDECK_H                  //If header hasn't been included before, then include it!

#include <stack>                //Include the stack template from the standard template library to be used for the deck
#include "blackjackCard.h"          //Include Card stub class to create and add arbitrary cards to the deck
#include <stdlib.h>             //Include for rand() and other standard functions


using namespace std;            //Ensure that included header files are using their own namespace

class blackjackDeck{                     //Class declaration for Deck class
    public:
        blackjackDeck();                 //Declare methods and variables as well as access modifiers for Deck class
        ~blackjackDeck();
        blackjackCard dealCard();
        void shuffleDeck();
        bool empty();
    protected:
    private:
    stack<blackjackCard> deck;           //Do not want public access to deck stack
};

#endif // DECK_H
