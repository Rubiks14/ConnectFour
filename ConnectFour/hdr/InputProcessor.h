#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <SDL.h>

class InputProcessor{
private:
	// no private members
protected:
	SDL_Event events;
	bool mousePressed;
public:
	int ProcessInput();
	bool ProcessQuit();
	SDL_Point ProcessMouseClick();
};

#endif