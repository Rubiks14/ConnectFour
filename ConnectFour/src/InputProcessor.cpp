#include "../hdr/InputProcessor.h"

#include <iostream>

int InputProcessor::ProcessInput(){
	SDL_PumpEvents();

	if (SDL_PeepEvents(&events, 1, SDL_GETEVENT, SDL_QUIT, SDL_MOUSEBUTTONUP)){
		return 0;
	}
	return -1;
}

bool InputProcessor::ProcessQuit(){
	if (events.type == SDL_QUIT){
		return true;
	}
	else if (events.type == SDL_KEYDOWN && events.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
		return true;
	}
	else{
		return false;
	}
}

SDL_Point InputProcessor::ProcessMouseClick(){
	SDL_Point mouseClickedAt = {-1, -1};
	if (events.type == SDL_MOUSEBUTTONDOWN){
		if (events.button.button == SDL_BUTTON_LEFT){
			mousePressed = true;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONUP && mousePressed){
		mouseClickedAt.x = events.button.x;
		mouseClickedAt.y = events.button.y;
		mousePressed = false;
	}
	return mouseClickedAt;
}