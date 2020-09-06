/*
 * This is the simplest class we have and it's only responsible for making a clear ctor and having the appropriate display.
 * The Deck class will use this as a key composition and the Poker Hand will actually give meaning to the game by evaluating 
 * these cards in tandem. 
 */
#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif 

#ifndef VECTOR_H
#define VECTOR_H
#include <vector> 
#endif 

#ifndef CARD_H
#define CARD_H

class Card {
	private:
		std::string cardValue;  // can't have these variables be const otherwise won't work with the Deck's shuffle method
		std::string cardSuit; 
	public: 
		Card(std::string val, std::string s): cardValue(val), cardSuit(s) {};  // ctor 
		std::string getCardSuit() const {return this->cardSuit;}
		std::string getCardValue() const {return this->cardValue;}
		void display(); 
};

void Card::display() {
	std::cout <<  getCardValue() << " of " << getCardSuit() << std::endl; 
}

#endif 
