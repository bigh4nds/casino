                                                                                                                    /*
AUTHOR: Chris Garry
        Software Intensive Engineering 373
        University of Massachusetts Amherst

DESCRIPTION:    1) Class to implement a 52 card deck using the stack data structure in the C standard template library
                2) Implementation of standard deck methods including dealing and shuffling

REVISION HISTORY: (1)2011-10-21-0128
TODO: See highlighted comments below
--------------------------------------------------------------------------------------------------------------------*/


//-----------PREPROCESSOR DIRECTIVES---------------//
#include "blackjackDeck.h"    //Include class declaration
#include <algorithm> //Convenient shuffle algorithm in STL
#include <vector>    //Vector is needed to shuffle objects

using namespace std; //Ensure STL includes are using independent namespace
//-----------END PREPROCESSOR DIRECTIVES-----------//


//----------------------BEGIN CLASS DEFINITION-----------------------------------------------------------------------


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    blackjackDeck::blackjackDeck(){                                   //Constructor for the Deck class to create a Deck object containing 52 card objects
        for(int index = 0; index <= 51; index++){   //index represents which card of the possible 52 is to be created
                blackjackCard x = blackjackCard(index);
                deck.push(x);                       //Add the new card to the deck stack
            }                                       //END FOR
    }                                               //END Deck()

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    blackjackDeck::~blackjackDeck(){                                  //Method to deconstruct
        //dtor
    }                                               //END ~Deck()
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    blackjackCard blackjackDeck::dealCard(){                          //Method to return a card from the deck by popping it off of the deck stack

        if(!deck.empty()){                          //Make sure deck is not empty
            blackjackCard x = deck.top();                    //Assign card at the top of the deck to x
            deck.pop();                             //Remove the item from the deck
            return x;
        }                                           //END IF

        return -1;                                   //Return card x
    }                                               //END dealCard()
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    bool blackjackDeck::empty(){                             //Helper method to dealCard() to determine if deck is empty

        return deck.empty();                        //Return boolean indicating true if deck is empty, false else
    }                                               //END empty()
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    void blackjackDeck::shuffleDeck(){                       //Shuffle the contents of the deck


        if(deck.size() != 0){

            vector<blackjackCard> tempDeck;             //Create an array to hold cards to be shuffled

            while(!deck.empty()){                       //Create a cardRand struct for each card in deck and place
                                                        //it in the array. Then sort the array according to the randID
                tempDeck.push_back(deck.top());
                deck.pop();
            }

             random_shuffle(tempDeck.begin(),tempDeck.end()); //This method comes from <algorithm> STL
                                                              //Shuffle the contents of the vector between indicies 0 and end of vetor


             for(unsigned int x = 0; x < tempDeck.size(); x++){     //Push shuffled contents of vector back into deck stack
                deck.push(tempDeck[x]);
             }

        }

    }
//--------------------END CLASS DEFINITION------------------------------------------------------------------------------------------


