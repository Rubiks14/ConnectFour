#ifndef GAME_DRAWER_H
#define GAME_DRAWER_H

#include "Renderer.h"
#include "Texture.h"
#include "Board.h"

class GameDrawer{
private:
	// no private members
protected:
	Texture* emptySquare;
	Texture* redPiece;
	Texture* blackPiece;

	int xOffset;
	int yOffset;

public:
	int loadTextures(Renderer* renderer);
	void drawBoard(Renderer* renderer, GameBoard* board);
};

#endif