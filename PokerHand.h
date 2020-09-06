
#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif 

#ifndef STRING_H
#define STRING_H
#include <string>
#endif 

#ifndef CTYPE_H
#define CTYPE_H
#include <cctype>
#endif 

#ifndef MAP_H
#define MAP_H
#include <map>
#endif 

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif 

#ifndef MEMORY_H
#define MEMORY_H
#include <memory>
#endif 

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <algorithm>
#endif 

#ifndef CARD_H
#define CARD_H
#include "Card.h" 
#endif 

/* This Class acts as an interface between the Card and the Player. It specifically transforms regular Cards 
 * into actual Poker values that can be evaluated and reflected in a payout. Most of the functions relate to 
 * evaluating any possible Poker hands from the 5 cards. 
 */
#ifndef POKERHAND_H
#define POKERHAND_H
class PokerHand { 

	private:
		std::vector<Card> hand; 
		int payout_multiplier{0}; 
	public: 
		PokerHand(const std::vector<Card> &vect);  // not allowing a default ctor -- need Card parameters 
		int getPayoutMult() { return this->payout_multiplier;} 
		// the below are evaluation functions for Poker hands 
		bool evalRoyalFlush(); 
	      	bool evalStraightFlush();
		bool evalFourKind();
		bool evalFullHouse();
		bool evalFlush();
		bool evalStraight();
		bool evalThreeKind();
		bool evalTwoPair();
		bool evalJacksOrBetter(); 
};


// ctor -> lowercase values are optional but thought it would be interesting to see how C++ worked with
// transforming strings to lowercase. We initialize our own Card hand to make Poker Hand evaluations 
PokerHand::PokerHand(const std::vector<Card> &vect) {
	std::string val, suit; 
	for (int i = 0; i < vect.size(); ++i) {
		val = vect[i].getCardValue(); 
		suit = vect[i].getCardSuit(); 
		std::transform(val.begin(), val.end(), val.begin(), ::tolower); 
		std::transform(suit.begin(), suit.end(), suit.begin(), ::tolower); 
		this->hand.push_back(Card(val, suit)); 
	}
}

// Jack or Better -> find exactly 1 pair of J, Q, K or A and nothing else 

bool PokerHand::evalJacksOrBetter() {
	// we can directly check for the other types of winnings by calling in order of rank precedence. 
	// If we win one of those hands, we'll exit out and the payout multiplier will accurately reflect that. 
	bool checkRF = evalRoyalFlush(); 
	bool checkSF = evalStraightFlush();
	bool check4k = evalFourKind();
	bool checkFullH = evalFullHouse(); 
	bool checkF = evalFlush(); 
	bool checkS = evalStraight(); 
	bool check3k = evalThreeKind();
	bool check2p = evalTwoPair(); 

	if (check2p or check3k or checkS or checkF or checkFullH or check4k or checkRF or checkSF) {
		return true; 
	}

	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	// initialize a dictionary to keep counts of each rank value . 
	std::map<std::string, int> rank_counts;
	for (int i = 0; i < seq.size(); ++i) {
		rank_counts[seq[i]] = 0;
	}

	for (int i = 0; i < this->hand.size(); ++i) {    // go through cards and update count 
		std::string rank_val = this->hand[i].getCardValue(); 
		if (rank_val == "jack" or rank_val == "queen" or rank_val == "king" or rank_val == "ace") {
			++rank_counts[rank_val]	; 
		}
	}
	std::map<std::string, int>::iterator itr; 
	int pair_count = 0 ; 				// increment this for each pair we find. 
	for (itr = rank_counts.begin(); itr != rank_counts.end(); ++itr) {
		if (itr->second == 2) {
			++pair_count; 
		}
	}
	if (pair_count == 1) {
		std::cout << "\nFound a Jack or better pair" << std::endl; 
		this->payout_multiplier = 1;
		return true; 
	}

	return false; 

}


// 2 pair -> find two pairs of cards that match in rank value. 
bool PokerHand::evalTwoPair() {
	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	// initialize a dictionary to keep counts of each rank value . 
	std::map<std::string, int> rank_counts;
	for (int i = 0; i < seq.size(); ++i) {
		rank_counts[seq[i]] = 0;
	}

	for (int i = 0; i < this->hand.size(); ++i) {    // go through cards and update count 
		std::string rank_val = this->hand[i].getCardValue(); 
		++rank_counts[rank_val]	; 
	}
	std::map<std::string, int>::iterator itr; 
	int pair_count = 0 ; 				// increment this for each pair we find. 
	for (itr = rank_counts.begin(); itr != rank_counts.end(); ++itr) {
		if (itr->second == 2) {
			++pair_count; 
		}
	}
	if (pair_count == 2) {
		std::cout << "\nFound a 2 pair" << std::endl; 
		this->payout_multiplier = 2;
		return true; 
	}

	return false; 

}

// This is a 3 of a kind function that works similarly to the 4 of a Kind or Full House in which we try to match up ranks. Here 
// we're concerned with only getting 3 cards of the same rank. 
bool PokerHand::evalThreeKind() {
	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	// initialize a dictionary to keep counts of each rank value . 
	std::map<std::string, int> rank_counts;
	for (int i = 0; i < seq.size(); ++i) {
		rank_counts[seq[i]] = 0;
	}

	for (int i = 0; i < this->hand.size(); ++i) {    // go through cards and update count 
		std::string rank_val = this->hand[i].getCardValue(); 
		++rank_counts[rank_val]	; 
	}
	std::map<std::string, int>::iterator itr; 
	bool three_found = false;
	for (itr = rank_counts.begin(); itr != rank_counts.end(); ++itr) {
		if (itr->second == 3) {
			three_found = true; 
		}
	}
	if (three_found) {
		std::cout << "\nFound a 3 Kind" << std::endl; 
		this->payout_multiplier = 3; 
		return true; 
	}

	return false; 

}

// straight -> this is very similar to the straight flush functionality below. We first create all the possible sequential 
// rank sequences using a vector of vectors. Then we iterate through each possibility and compare each one to our hand. 
// Once a possibility rank-sequence fully matches with our hand, we can return true. 
bool PokerHand::evalStraight() {
	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	std::vector<std::vector<std::string>> all_poss;  // vector of vectors 
	std::vector<std::string> poss;
	for (int i = 0; i < seq.size() - 4; ++i) { // once you reach the 9th card, can't add 5 cards anymore 
		for (int j = i; j < i+5; ++j) {
			poss.push_back(seq[j]); 
		}
		all_poss.push_back(poss); 
		poss.clear();
	}
	int match_count; 
	std::string val; 
	for (int i = 0; i < all_poss.size(); ++i) {  // iterate through all the combinations 
		poss = all_poss[i]; 
		for (int j = 0; j < this->hand.size(); ++j) {  // iterate through entire hand 
			val = this->hand[j].getCardValue(); 
			for (int z = 0; z < poss.size(); ++z) {  // iterate through all of current possibility to match 
				if (val == poss[z]) {
					++match_count; 
				}
			}
		}
		match_count = 0;  // reset match_count for the next rank-seq possibility 
		if (match_count == 5) { 
			this->payout_multiplier = 4;		// if match found, we can return true  
			std::cout << "\nFound a Straight" << std::endl; 
			return true; 
		}
		match_count = 0; 	
	}
	return false; 

}

// Flush -> simply check if there is a mismatched suit among the cards in our hand. 
bool PokerHand::evalFlush() {
	std::string suit = this->hand[0].getCardSuit(); 
	std::string check_suit; 
	for (int i = 0; i < this->hand.size(); ++i) {      // check if all matching suits. If not, then we can return out now. 
		check_suit = this->hand[i].getCardSuit(); 
		if (check_suit != suit) {
			return false; 
		}
	}
	std::cout << "\nFound a flush " << std::endl;
	this->payout_multiplier = 6; 

	return true; 
}

// Full House works by creating a dictionary hash map for the ranks and then searching through the hand to see if we found 
// a count match for 3 and 2 -> full house 
bool PokerHand::evalFullHouse() {
	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	// initialize a dictionary to keep counts of each rank value . 
	std::map<std::string, int> rank_counts;
	for (int i = 0; i < seq.size(); ++i) {
		rank_counts[seq[i]] = 0;
	}

	for (int i = 0; i < this->hand.size(); ++i) {    // go through cards and update count 
		std::string rank_val = this->hand[i].getCardValue(); 
		++rank_counts[rank_val]	; 
	}
	std::map<std::string, int>::iterator itr; 
	bool three_found = false, two_found = false; 
	for (itr = rank_counts.begin(); itr != rank_counts.end(); ++itr) {
		if (itr->second == 3) {
			three_found = true; 
		}
		if (itr->second == 2) {
			two_found = true; 
		}
	}
	if (three_found and two_found) {
		std::cout << "\nFound a Full House" << std::endl; 
		this->payout_multiplier = 9; 
		return true; 
	}

	return false; 

}

// 4 Kind works similarly to Full House by creating a dictionary hash map for the ranks and then searching through the hand to see if we found 
// a count match for 3 and 2 -> full house 

bool PokerHand::evalFourKind() {
	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	std::map<std::string, int> rank_counts;
	for (int i = 0; i < seq.size(); ++i) {
		rank_counts[seq[i]] = 0;
	}

	for (int i = 0; i < this->hand.size(); ++i) {
		std::string rank_val = this->hand[i].getCardValue(); 
		++rank_counts[rank_val]	; 
	}
	std::map<std::string, int>::iterator itr; 
	for (itr = rank_counts.begin(); itr != rank_counts.end(); ++itr) {
		if (itr->second >= 4) {
			std::cout << "\nFound a 4 kind" << std::endl;
			this->payout_multiplier = 25; 
			return true; 
		}
	}

	return false; 
}

// evalStraightFlush() -> check if there is a rank sequence, all same suit, but not royal flush. 
// Gather all the possible combinations of getting a sequential 5-card sequence. Then for each of these 
// combinations, we need to check if our current 5 card set has any matches with any of the possibility sets. 
bool PokerHand::evalStraightFlush() { 
	std::vector<std::string> seq = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"}; 
	std::vector<std::vector<std::string>> all_poss;  // vector of vectors 
	std::vector<std::string> poss;
	for (int i = 0; i < seq.size() - 4; ++i) { // once you reach the 9th card, can't add 5 cards anymore 
		for (int j = i; j < i+5; ++j) {
			poss.push_back(seq[j]); 
		}
		all_poss.push_back(poss); 
		poss.clear();
	}
	all_poss.push_back({"10", "jack", "queen", "king", "ace"}); // last possible combo 
	std::string suit = hand[0].getCardSuit(); 
	std::string check_suit; 
	for (int i = 0; i < this->hand.size(); ++i) {      // check if all matching suits. If not, then we can return out now. 
		check_suit = this->hand[i].getCardSuit(); 
		if (check_suit != suit) {
			return false; 
		}
	}
	int match_count; 
	std::string val; 
	for (int i = 0; i < all_poss.size(); ++i) {  // iterate through all the combinations 
		poss = all_poss[i]; 
		for (int j = 0; j < this->hand.size(); ++j) {  // iterate through entire hand 
			val = this->hand[j].getCardValue(); 
			for (int z = 0; z < poss.size(); ++z) {  // iterate through all of current possibility to match 
				if (val == poss[z]) {
					++match_count; 
				}
			}
		}
		if (match_count == 5) { 
			this->payout_multiplier = 50;		// if match found, we can return true  
			std::cout << "\nFound a Straight Flush!" << std::endl;
			return true; 
		}
		match_count = 0; 	
	}
	return false; 
}


// evalRoyalFlush() -> check if there is a royal flush [10, J, K, Q, A all of same suit] 
bool PokerHand::evalRoyalFlush() {
	bool isTen = false, isJack = false, isKing = false, isQueen = false, isAce = false; 
	std::string val;
	std::string suit = this->hand[0].getCardSuit(); 
	for (int i = 0; i < this->hand.size(); ++i){
		val = this->hand[i].getCardValue();
		std::string check_suit = this->hand[i].getCardSuit();  // if suit differs, then break out 
		if ((val == "10") and (check_suit == suit)) {
			isTen = true;
		}
		else if ((val == "jack") and (check_suit == suit)) {
			isJack = true;
		}
		else if ((val == "king") and (check_suit == suit)) {
			isKing = true; 
		}
		else if ((val == "queen") and (check_suit == suit)) {
			isQueen = true; 
		}
		else if ((val == "ace") and (check_suit == suit)) {
			isAce = true; 
		}
		else {  // no royal flush found -- break out. 
			return false; 		
		}
	}
	if (isTen and isJack and isKing and isQueen and isAce) {
		this->payout_multiplier = 250;  // winnings 
		std::cout << "\nFound a Royal Flush!" << std::endl; 
		return true; 
	}
	return false; 
}



#endif 
