/*
 * This Class acts as the main interface to start the Poker game. This is similar to the UI interface we worked on in class/hw. 
 * Here we have a composition of objects -> Deck, Player, Card, PokerHand to keep track of our current Hand. We have 
 * various functions to deal the hand, pique the Player to execute some deposits and make bets, and evaluate the Poker hands. 
 */
#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif 

#ifndef STRING_H
#define STRING_H
#include <string>
#endif 

#ifndef SSTREAM_H
#define SSTREAM_H
#include <sstream>
#endif 

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "PokerHand.h" 

class Game {
	private: 
		Player* p1; 
		Deck* deck; 
		std::vector<Card> currHand; 
		const int handSize{5}; 
		int deposit; 
		int bet; 
		bool play{true}; 
	public:
		Game(Player* p, Deck* d): p1(p), deck(d) {}; 
		void executeDeposit();
		void executeBet(); 
		void dealHand(); 
		std::vector<int> getCardids(); // helper function for dealHand()
		void evaluateHand();
		void startGame();
		void endGame();
		void continuePlay();
};

// Actually starting the game. This is the main functionality behind this interface. The game will keep going as 
// long as the the play boolean variable is true. Once it's false, the player will cashout. 
void Game::startGame() {
	executeDeposit();
	while (this->play) { 
		executeBet();
		dealHand();
		evaluateHand();
		continuePlay();
	}
	p1->cashout(); 
}


// This function allows for the continuation of the Game after the bets and evaluations are done. The user will have to 
// input a 1 to keep playing. If he does, then he will be prompted to make a deposit as well to his bankroll. 
// In both prompts, he can quit. If he quits at the first prompt, the game will end ("this->play = false"). 
// If he quits at the second prompt, no deposit will be made. Some defensive programming has been implemented as well. 
void Game::continuePlay() {
	int testInput; 
	std::cout << "Do you want to keep playing? If so, enter 1, else anything to exit" << std::endl; 
	std::cin >> testInput; 
	if (std::cin && testInput == 1) {  
		std::cin.clear();
		fflush(stdin); 
		this->play = true; 
		std::cout << "Okay, do you want to make another deposit? Same as before: Enter 1 if so" << std::endl; 
		std::cin >> testInput; 
		if (std::cin && testInput == 1) {
			std::cin.clear(); 
			executeDeposit();
		}
		else {
			std::cin.clear(); 
			fflush(stdin); 
		}
	}
	else {
		exit(0); 
	}
}

// This function ends the game if the player has no more money left in his savings (not bankroll). 
void Game::endGame() {
	std::cout << "Welp! Get some more money and come back later!" << std::endl; 
	exit(1);
}

// The player is prompted to make a valid deposit into his bankroll from his savings. 
void Game::executeDeposit() {
	bool valid_deposit = false;
	while (!valid_deposit) {
		std::cout << "Enter some coins into bankroll!" << std::endl;
		std::cin >> this->deposit; 
		valid_deposit = p1->depositToBankroll(this->deposit); 
		if (valid_deposit && (p1->getCurrentMoney() == 0)) {
			endGame();
		}
	}
}

// The player is prompted to make a valid bet between 1 and 5. If the return value from makeBet is false, 
// then we check whether that was because it was a valid bet but there weren't enough coins in the bankroll.
// If so, then the player has to make another deposit to replenish the bankroll. 
void Game::executeBet() {
	bool valid_bet = false;
	while (!valid_bet) {
		std::cout << "Enter a bet!" << std::endl; 
		std::cin >> bet; 
		valid_bet = p1->makeBet(this->bet); 
		if (valid_bet == false && (this->bet >= 1 && this->bet < 5)){
			executeDeposit(); 
		}
	}
}


//  This is a helper function to get user input as a stream of integers. These integers will match 
//  the Card numbers that will be displayed to stdout so the user will have to match the cards he wants to replace. 
std::vector<int> Game::getCardids() {
	std::vector<int> cardIDsToReplace; 
      	int x =0 ;  
	std::cout << "Enter \'q\' if you want to exit. Carriage return to enter another num" << std::endl;
	std::string mystr; 
	int count = 0; 
	std::getline(std::cin, mystr, 'q'); 
	std::stringstream sstream(mystr); 
	while (sstream >> x) { 
		if (x >= 1 and x <= 5) { 			 // only valid input will be added 
			cardIDsToReplace.push_back(x); 
			++count; 
			if (count == 5) return cardIDsToReplace;  // in case user has put in more input. 
		}
	}
	return cardIDsToReplace; 
}

// This function makes a new hand based on the cards that the player wants to replace. 
void Game::dealHand() {
	deck->resetDeck();
	deck->shuffle(); 	
	for (int i = 0; i < handSize; ++i) {
		this->currHand.push_back(deck->deal()); 
	}
	std::cout << "Here are your cards. Choose the #s of the cards you would like to replace" << std::endl; 
	for (int i = 0; i < handSize; ++i) {
		std::cout << "Card #" << i+1 << "->";
		this->currHand[i].display(); 
	}
	std::cout << "\n" << std::endl; 
	std::vector<int> replaced;   // will hold the ids of the cards to replace 
	std::vector<int> cardIDsToReplace= getCardids(); // return result from helper function above 
	std::vector<Card> tempHand;  
	// dangerous to "erase" while iterating so we create a temporary hand that has all the currHand's cards.
	// We will then clear the currHand and add new cards for each replaced ID that's detected. 
	// We will then add back the old cards to the currHand 
	for (int i = 0; i < handSize; ++i) {
		tempHand.push_back(this->currHand[i]);  
	}
	this->currHand.clear(); // remove everything from current hand 
	int num = 0; 
	for (int i = 0; i < cardIDsToReplace.size(); ++i) {
		num = cardIDsToReplace[i]; 
		--num; // because player will see x from 1-5 instead of 0-4 which we need for indexing 
		if (num <= 4 and num >= 0) {
			std::cout << "replacing card id " << num+1 << std::endl; 
			this->currHand.push_back(deck->deal());  // add new cards for each "replaced" that's detected 
			replaced.push_back(num); 
		}
	}
	std::map<int, int> addbacks; 
	for (int i = 0; i < handSize; ++i) {  // initialize a dictionary mapping
		addbacks[i] = 0; 
	}
	for (int j = 0; j < replaced.size(); ++j) {  // for every replaced id we encounter, we increment by 1 
		++addbacks[replaced[j]];
	}
	std::map<int, int>::iterator itr; 
	for (itr = addbacks.begin(); itr != addbacks.end(); ++itr) {
		if (itr->second == 0) {				// we only add the non-replaced cards based on id 
			this->currHand.push_back(tempHand[itr->first]); 
		}
	}
	std::cout << "\nNew hand: " << std::endl;
	for (int i = 0; i < handSize; ++i) {
		this->currHand[i].display(); 
	}
}

// This function evaluates the current Hand with the Poker game rules of scoring hands. 
// Any winnings will be reflected in the bankroll. A clear display is shown and then the hand is erased for
// the next game. 
void Game::evaluateHand() {
	PokerHand phand(this->currHand); 
	bool winHand = phand.evalJacksOrBetter(); // will evaluate every possible hand 
	int payMult = 0; 
	if (winHand) {
		payMult = phand.getPayoutMult(); 
		int winnings = payMult * this->bet;  // get the winnings and add it back to our player 
		std::cout << "you won " << winnings << " coins" << std::endl; 
		p1->addWinnings(winnings); 
		std::cout << std::endl;
	}
	else {
		std::cout << "Didn't win :(\n " << std::endl; 
	}
	p1->display(); 
	std::cout << std::endl; 
	this->currHand.clear();  		// we're done with the hand so we can clear it 
}

