

// driver that uses the Game class as the engine behind the scenes. We initialize a player with a savings of $500 and a deck. 
#include <iostream>
#include "Game.h"

int main() {
	Player tom("Tom", 500);
	Deck deck; 
	Game poker(&tom, &deck); 
	poker.startGame();
	return 0 ;
}
