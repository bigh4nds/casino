/*
    Pot.h
    Header file for Pot Class
*/

#ifndef BLACKJACKPOT_H
#define BLACKJACKPOT_H

class blackjackPot{
    private:
    int potValue;

    public:
    blackjackPot(int);
    void addToPot(int);
    void clearPot();
    int getValue();
};
#endif
