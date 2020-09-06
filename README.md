
## *Specs*

>Compiled on a (x86-64) MacOS Catalina with clang 11.0.3 using C++11
>
> To Run: a simple make should suffice and "./start" will start the command-line game 

## Game Info 

A game simulating a single hand of 5-card stud poker. 

### Rules 

1. Player deposits # of coins as a starting bankroll. All coins have the same value 
	a. Note that Player starts out with 500 coins to his or her name. The bankroll is what the Player brings to the casino itself. If the 500 coins run out, the Player has nothing and has bigger concerns than winning.  
2. Player makes a bet between 1 and (including) 5 coins 
3. 5 cards are dealt as a hand. After viewing the hand, the player can select which card(s) to discard and replace. 
4. The same number of discarded cards are replaced with new cards and immediately afterwards, the hand is scored (scoring scheme below).
5. Based on the hand, the winning amount is added to the bankroll otherwise the bet amount is deducted from bankroll. 
6. The player can quit anytime after each card hand is evaluated and can also add to his/her bankroll. 

### Scoring 

The card are evaluated by rank and suit. 

1. Suits -> Hearts, Diamonds, Clubs, Spades 
2. Rank -> Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King
3. The following are rank-suit combos in descending order of winning priority. In other words, the first item, Royal Flush, will dominate all the other combinations. There can only be one winning hand so if a Player gets a Royal Flush, only the winning amount for the Royal Flush will be added to the bankroll (e.g. only 250 coins) 

> Royal Flush - 10, Jack, King, Queen, Ace, all of the same suit. Pays 250 to 1.
>
> Straight Flush: Five cards in rank sequence, all of the same suit, but not a royal
flush. Pays 50 to 1 
>
> Four of a Kind: For cards of the same rank. Pays 25 to 1 
> 
> Full House: Three cards of one rank and two of another. Pays 9 to 1 
>
> Flush: All five cards of the same suit, but not a straight flush. Pays 6 to 1
>
> Straight: Five cards in rank sequence, but not a flush. Pays 4 to 1
>
> Three of a Kind: Three cards of the same rank and two cards of two other ranks
that is not a full house or four of a kind. Pays 3 to 1 
>
> Two Pair: Two cards of one rank, two of another, and one card of a third. Pays 2 to 1.
>
> Jacks or Better: Exactly one pair of Jacks, Queens, Kings, or Aces, and nothing
else of interest. Pays 1 to 1 
   
 


