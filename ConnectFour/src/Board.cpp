#include "../hdr/Board.h"

#include <iostream>

GameBoard::GameBoard(){
	init();
}

GameBoard::~GameBoard(){
	close();
}

int GameBoard::init(){
	// create an empty square to occupy the vector with
	BoardSquare empty;
	empty.occupied = false;
	empty.color = NO_COLOR;

	// clear anything in the vector (used mainly when replaying)
	squares.clear();

	// loop through 
	for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++){
		//if (i % 5 == 0){
		//	empty.occupied = true;
		//	empty.color = RED;
		//}
		//else if (i % 3 == 0){
		//	empty.occupied = true;
		//	empty.color = BLACK;
		//}
		//else{
		//	empty.occupied = false;
		//	empty.color = NO_COLOR;
		//}
		squares.push_back(empty);
	}

	// only returns 0 for now
	return 0;
}

int GameBoard::close(){
	squares.clear();

	return 0;
}

bool GameBoard::insertPiece(int col, int occupiedByColor){
	for (int i = BOARD_HEIGHT - 1; i >= 0; i--){
		if (isOccupied(i, col) != true){
			int position = i * BOARD_WIDTH + col;
			squares[position].color = occupiedByColor;
			squares[position].occupied = true;
			squares[position].row = i;
			squares[position].col = col;
			
			return true;
		}
		else if (i == 0){
			return false;
		}
	}
	return false;
}

bool GameBoard::isOccupied(int row, int col){
	return squares[row * BOARD_WIDTH + col].occupied;
}

int GameBoard::occupiedBy(int row, int col){
	return squares[row * BOARD_WIDTH + col].color;
}