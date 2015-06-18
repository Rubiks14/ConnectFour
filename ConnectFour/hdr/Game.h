#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "GameDrawer.h"
#include "InputProcessor.h"

class Game{
private:
	// no private members
protected:
	Renderer* renderer;
	GameDrawer* drawer;
	GameBoard* board;
	InputProcessor* input;
	int playerTurn;

	bool checkWin(int color);

	void redWins();
	void blackWins();
	void playersDraw();
public:
	Game();
	~Game();

	int init();
	int process();
	int draw();
	int end();
};

#endif