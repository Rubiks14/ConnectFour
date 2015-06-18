#ifndef BOARD_H
#define BOARD_H

#include <vector>


// color of pieces that can occupy squares on the board
const int NO_COLOR = 0;
const int RED = 1;
const int BLACK = 2;

// board size
const int BOARD_WIDTH = 7;
const int BOARD_HEIGHT = 6;


// a struct that will be used to represent a square on the board
// this is only used by the GameBoard class
struct BoardSquare{
public:
	bool occupied;
	int color;
	int row, col;
};

// the game board
class GameBoard{
private:
	// no private members
protected:
	std::vector<BoardSquare> squares;
public:
	// constructor and destruction.
	GameBoard();
	~GameBoard();

	// theses methods actually initialize and close the class respectively
	int init();
	int close();

	// change state of the board
	bool insertPiece(int, int);

	// get states of the board
	bool isOccupied(int, int);
	int occupiedBy(int, int);
};

#endif