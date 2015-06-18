#include "../hdr/GameDrawer.h"

int GameDrawer::loadTextures(Renderer* renderer){
	emptySquare = new Texture("rsc/EmptySquare.png", renderer->getRenderer());
	blackPiece = new Texture("rsc/BlackPiece.png", renderer->getRenderer());
	redPiece = new Texture("rsc/RedPiece.png", renderer->getRenderer());


	return 0;
}

void GameDrawer::drawBoard(Renderer* renderer, GameBoard* board){
	// current row and column to determine draw position
	// also used to check for occupied squares and draw
	// the appropriate game piece in non-empty squares
	int currentRow = 0;
	int currentCol = 0;

	xOffset = 96;
	yOffset = 256;


	// rect to hold the position to draw each square and
	// game piece. size is hard coded right now. also
	// size is scaled up
	SDL_Rect drawPosition;
	drawPosition.w = 64;
	drawPosition.h = 64;
	
	// we always draw every game square
	for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++){
		
		// make sure that we don't need to change rows
		// the column is reset when the row changes.
		if (currentCol >= BOARD_WIDTH){
			currentRow++;
			currentCol = 0;
		}

		// grab the draw position based on the width
		// and height multiplied by Col and Row respectively
		drawPosition.x = drawPosition.w * currentCol + xOffset;
		drawPosition.y = drawPosition.h * currentRow + yOffset;

		// check to see if the current position is occupied
		// if it is then we check the color occupying the square
		// and draw the appropriate game piece to match the color
		if (board->isOccupied(currentRow, currentCol)){
			Texture *tempTexture = emptySquare;
			switch (board->occupiedBy(currentRow, currentCol))
			{
			case RED:
				tempTexture = redPiece;
				break;
			case BLACK:
				tempTexture = blackPiece;
				break;
			default:
				break;
			}
			renderer->drawToRenderer(tempTexture->getTexture(), drawPosition);
		}

		// finally draw the game square and move to the next column
		renderer->drawToRenderer(emptySquare->getTexture(), drawPosition);
		currentCol++;
	}
}