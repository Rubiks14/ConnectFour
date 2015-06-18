#include <SDL.h>
#undef main

#include "../hdr/Game.h"

int main(int argc, char *argv[]){
	Game* game = new Game();
	game->init();
	game->process();
	game->end();
	return 0;
}