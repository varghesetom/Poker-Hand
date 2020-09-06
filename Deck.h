/*
 * This class deals with creating a deck of cards (so a composition with the Card object). We have some 
 * const class variables that we can use to make our deck (which is deque). We have a few private variables 
 * dealing with the idea of dealt cards. If we have dealt cards, that means we would need to add them back into our 
 * deck to get back to the full 52. This is necessary otherwise the probabilities behind our Poker hands will 
 * become skewed. The Game class is responsible for making sure that the deck is shuffled properly afterwards. 
 */

#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif 

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <algorithm>
#endif 

#ifndef DEQUE_H
#define DEQUE_H
#include <deque>
#endif 

#ifndef RANDOM_H
#define RANDOM_H
#include <random> 
#endif 

#include <optional>

#ifndef CHRONO_H
#define CHRONO_H
#include <chrono>
#endif 

#ifndef DECK_H
#define DECK_H

class Deck {
	const std::vector<std::string> suits = {"Hearts", "Clubs", "Spades", "Diamonds"}; 
	const std::vector<std::string> values = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"}; 
	private: 
		std::deque<Card> deck;
		bool dealt{false}; 
		std::vector<Card> dealtCards; 
	public:
		Deck();
		Card deal();
		void shuffle(); 
		int countRemaining() { return this->deck.size(); } 
		std::deque<Card> getDeck() {return this->deck;}
		void resetDeck(); 
		void display() ;
};
		
// Ctor 
Deck::Deck() {
	std::string suit, val; 
	for (int i = 0; i < suits.size(); ++i) {
		for (int j = 0; j < values.size(); ++j) {
			val = values[j]; 
			suit = suits[i]; 
			this->deck.push_back(Card(val, suit));
		}
	}
}

// return a card if there are cards remaining in the deck. If the deck, is empty, return empty. 
Card Deck::deal() {
	Card c = this->deck.front();
	dealt = true ;
	dealtCards.push_back(c); // add the dealt card to our vector 
	this->deck.pop_front();  // delete 
	return c; 
}

// using a C++ way of shuffling cards based on the current time as the seed for our RNG 
void Deck::shuffle() {
	unsigned rd = std::chrono::system_clock::now().time_since_epoch().count();  // get a seed based on time right now
       	auto rng = std::default_random_engine{rd}; 
	std::shuffle(std::begin(this->deck), std::end(this->deck), rng);	
}

// reset the deck after having dealt some cards. 
void Deck::resetDeck() {
	if (dealt) {
		for (int i = 0; i < dealtCards.size(); ++i) {
			deck.push_back(dealtCards[i]);   // adding back the dealt cards back into our deck 
		}
	}
}

// display function to see all the remaining cards in the deck
void Deck::display() {
	for (int i = 0; i < this->deck.size(); ++i) {
		std::cout << "Card: " << deck[i].getCardValue() << " of " << deck[i].getCardSuit(); 
	}
}

#endif 
