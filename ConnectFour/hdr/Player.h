#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Board.h"

class Player{
private:
	// no private members
protected:
	std::string name;
	int color;
	int longestStreak;
	bool isWinner;
public:
	Player();
	~Player();

	int init();
	int close();

	int processTurn(int);
};

#endif