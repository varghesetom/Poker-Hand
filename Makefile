## This is a makefile for our Poker Game. We use the C++11 compiler 
CC=g++ -g -Wall -std=c++11 
TARGET=start

$(TARGET): start.cpp Game.h Player.h Card.h Deck.h PokerHand.h
	$(CC) start.cpp -o start

.PHONY:clean
clean: 
	rmtrash $(TARGET) 
	rmtrash $(TARGET).dSYM



