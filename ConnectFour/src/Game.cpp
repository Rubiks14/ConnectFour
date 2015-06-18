#include "../hdr/Game.h"

Game::Game(){}

Game::~Game(){}

int Game::init(){
	renderer = new Renderer("Connect Four", 640, 640, SDL_WINDOW_SHOWN);
	drawer = new GameDrawer();
	drawer->loadTextures(renderer);
	input = new InputProcessor();
	board = new GameBoard();

	playerTurn = 1;

	return 0;
}

int Game::process(){
	bool gameOver = false;
	while (!input->ProcessQuit() && gameOver != true){
		input->ProcessInput();
		SDL_Point mousePos = input->ProcessMouseClick();
		if (mousePos.x != -1 && mousePos.y != -1){

			// (TODO) move offset values to variables. xOffset = 96 yOffset = 256
			if (mousePos.x <= BOARD_WIDTH * 64 + 96 && mousePos.y <= BOARD_HEIGHT * 64 + 256 && mousePos.x >= 96){
				int col = (mousePos.x - 96) / 64;

				// debug info
				std::cout << "column: " << col << "\t";
				std::cout << "Mouse click location: " << "(" << mousePos.x << "," << mousePos.y << ")\n";

				if (playerTurn == 1 && board->insertPiece(col, RED)){
					if (checkWin(RED) == true){
						redWins();
						gameOver = true;
					}
					playerTurn = 2;
				}
				else if (playerTurn == 2 && board->insertPiece(col, BLACK)){
					if (checkWin(BLACK) == true){
						blackWins();
						gameOver = true;
					}
					playerTurn = 1;
				}
				else{
					std::cout << "This column is full. Please place your piece elsewhere.\n";
					if (checkWin(NO_COLOR) == true){
						playersDraw();
						gameOver = true;
					}
				}
			}
		}
		draw();
	}
	return 0;
}

bool Game::checkWin(int color){

	// Horizontal (this also checks if all peices are filled for a draw Scenerio.)
	int occupiedCount = 0;
	for (int row = BOARD_HEIGHT - 1; row >= 0; row--){
		int count = 0;
		for (int col = 0; col < BOARD_WIDTH; col++){
			if (board->isOccupied(row, col)){
				occupiedCount++;
				if (occupiedCount >= BOARD_WIDTH * BOARD_HEIGHT){
					std::cout << "It's a draw.\n";
					return true;
				}
			}
			if (board->isOccupied(row, col) && board->occupiedBy(row, col) == color){
				count++;
			}
			else{
				count = 0;
			}
			if (count == 4){
				std::cout << "a winner has been found!!\n";
				return true;
			}
		}
	}

	// Verticle
	for (int col = 0; col < BOARD_WIDTH; col++){
		int count = 0;
		for (int row = BOARD_HEIGHT - 1; row >= 0; row--){
			
			if (board->isOccupied(row, col) && board->occupiedBy(row, col) == color){
				count++;
			}
			else{
				count = 0;
			}
			if (count == 4){
				std::cout << "a winner has been found!!\n";
				return true;
			}
		}
	}

	// UP_LEFT to DOWN_RIGHT
	for (int col = 0; col < BOARD_WIDTH; col++){
		int count = 0;
		for (int row = 0; row <= BOARD_HEIGHT / 2; row++){
			if (!board->isOccupied(row, col) || board->occupiedBy(row, col) != color){
				continue;
			}
			else if (row + 1 >= BOARD_HEIGHT || col + 1 >= BOARD_WIDTH || !board->isOccupied(row + 1, col + 1) || board->occupiedBy(row + 1, col + 1) != color){
				continue;
			}
			else if (row + 2 >= BOARD_HEIGHT || col + 2 >= BOARD_WIDTH || !board->isOccupied(row + 2, col + 2) || board->occupiedBy(row + 2, col + 2) != color){
				continue;
			}
			else if (row + 3 >= BOARD_HEIGHT || col + 3 >= BOARD_WIDTH || !board->isOccupied(row + 3, col + 3) || board->occupiedBy(row + 3, col + 3) != color){
				continue;
			}
			else{
				std::cout << "a winner has been found!!\n";
				return true;
			}
		}
	}

	// UP_RIGHT to DOWN_LEFT
	for (int col = BOARD_WIDTH / 2; col < BOARD_WIDTH; col++){
		int count = 0;
		for (int row = 0; row <= BOARD_HEIGHT / 2; row++){
			if (!board->isOccupied(row, col) || board->occupiedBy(row, col) != color){
				continue;
			}
			else{
				if (row + 1 >= BOARD_HEIGHT || col - 1 < 0 || !board->isOccupied(row + 1, col - 1) || board->occupiedBy(row + 1, col - 1) != color){
					continue;
				}
				else if (row + 2 >= BOARD_HEIGHT || col - 2 < 0 || !board->isOccupied(row + 2, col - 2) || board->occupiedBy(row + 2, col - 2) != color){
					continue;
				}
				else if (row + 3 >= BOARD_HEIGHT || col - 3 < 0 || !board->isOccupied(row + 3, col - 3) || board->occupiedBy(row + 3, col - 3) != color){
					continue;
				}
				else{
					std::cout << "a winner has been found!!\n";
					return true;
				}
			}
		}
	}
	return false;
}

void Game::redWins(){
	// type the red wins text here.
	SDL_Color fontColor;
	fontColor.r = 127;
	fontColor.g = 50;
	fontColor.b = 50;
	SDL_Rect textDrawLocation;
	textDrawLocation.x = 0;
	textDrawLocation.y = 0;
	textDrawLocation.h = 50;
	textDrawLocation.w = 200;
	TTF_Font* textFont = TTF_OpenFont("C:/Windows/Fonts/Areil.ttf", 50);
	renderer->drawText("Red Player has Won!", textFont, fontColor, textDrawLocation);
	renderer->update();
	SDL_Delay(500);
}
void Game::blackWins(){}
void Game::playersDraw(){}

int Game::draw(){
	renderer->clearRenderer(255, 255, 255);
	drawer->drawBoard(renderer, board);
	renderer->update();

	return 0;
}

int Game::end(){
	delete renderer;
	delete drawer;
	delete input;
	delete board;
	IMG_Quit();
	SDL_Quit();

	return 0;
}