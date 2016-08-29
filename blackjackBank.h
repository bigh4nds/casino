/** blackjackBank class header
 ** author: Christopher Finn
 **/
#ifndef BLACKJACKBANK_H
#define BLACKJACKBANK_H

class blackjackBank{
	private:
	int bankTotal;

	public:
	blackjackBank();
	blackjackBank(int);
	int getTotal();
	void updateTotal(int);
	int returnTotal();
};
#endif
