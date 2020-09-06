/* 
 * This class deals with creating a Player who can move his money around from his savings to his bankroll and back out 
 * again to his savings (if he cashouts and actually, you know, won). The primary methods that the Player is responsible 
 * for is actually making a valid deposit(s) to his bankroll, a valid bet and cashing out. The validity of these functions 
 * are worked on with some defensive programming to check for valid inputs. 
 */
#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream> 
#endif 

#ifndef STRING_H
#define STRING_H
#include <string> 
#endif 

#ifndef MEMORY_H
#define MEMORY_H
#include <memory>
#endif 

#ifndef PLAYER_H
#define PLAYER_H

class Player { 
	private:
		const std::string name; 
		int moneyForPoker; 
		int bankroll{0}; 
	public:
		Player(std::string n, int savings): name(n), moneyForPoker(savings) {}; 
		~Player();
		std::string getName() const { return this->name; } 
		int getBankroll() { return this->bankroll; }  
		int getCurrentMoney() { return this->moneyForPoker;} 
		void subtractCurrentMoney(int);
		void addWinnings(int); 
		bool makeBet(int);
		bool depositToBankroll(int);  // bankroll "setter" method 
		void cashout(); 
		void display(); 
};

// dtor  -> to show that the game has ended after cashing out. 
Player::~Player() {
	std::cout << "\nPlayer has left Poker Table...\n"; 
}

// addWinnings -> add the winnings to the current bankroll 
void Player::addWinnings(int winnings) {
	this->bankroll += winnings; 
}

// subtractCurrentMoney -> subtract money amt from the moneyForPoker. 
void Player::subtractCurrentMoney(int amtToSubtract) {
	this->moneyForPoker -= amtToSubtract; 
}

// This function allows the player to make a valid bet. 
bool Player::makeBet(int bet) {
	int currBankroll = getBankroll(); 
	if (bet > 5 or bet < 1) {
		std::cout << "Not a possible bet. Bet needs to be between 1 and 5\n"; 
		return false; 
	}
	if (bet > currBankroll) {    // in the case that bet is larger than bankroll
		std::cout << "You're betting more than what's in your bankroll. Bet fewer or add more coins to broll\n";
		return false; 
	}
	this->bankroll -= bet;      // add to bankroll 
	return true; 
}
	
// depositToBankRoll -> after initializing player with current money playing at casino,
// can only add to bankroll from that cash. Once current money is initialized, it cannot be changed 
bool Player::depositToBankroll(int somePlayMoney) {
	int currMoney = getCurrentMoney(); 
	if (getCurrentMoney() == 0) {			  // check bankruptcy  
		std::cout << "You lost your entire savings at poker! Have a good day" << std::endl; 
		return false;
	}
	else if (somePlayMoney > currMoney) {             // in the case that bet is larger than money left  
		std::cout << "Not enough money to deposit into machine!" << std::endl; 
		return false; 
	}
	else if (somePlayMoney < 0) {
		std::cout << "How can you deposit a negative amount bro? Try again\n" << std::endl;
		return false; 
	}
	this->bankroll += somePlayMoney;      // add to bankroll 
	subtractCurrentMoney(somePlayMoney); // subtract from total money 
	return true; 
}

// cash out and quit -> add the total bankroll to current money 
void Player::cashout() {
	std::cout << this->name << " is cashing out with " << this->bankroll << " in his bankroll" << std::endl; 
	std::cout << "Adding " << this->bankroll << " coins to current $" << this->moneyForPoker << std::endl; 
	this->moneyForPoker += this->bankroll; 
	this->bankroll -= this->bankroll; 
	std::cout << this->name << " has cashed out and left. Current money: " << this->moneyForPoker; 
}

void Player::display() {
	std::cout << "Player: " << this->name << std::endl; 
	std::cout << "Current Money Left for Poker: " << this->moneyForPoker << std::endl;
	std::cout << "Current Bankroll: " << this->bankroll << std::endl; 
}


#endif 
