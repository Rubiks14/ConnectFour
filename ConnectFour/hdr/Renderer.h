#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class Renderer {
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture * renderFrame;
		SDL_Rect screenSize;

	public:
		Renderer(void);
		Renderer(std::string name, int width, int height, Uint32 flags);
		~Renderer(void);

		SDL_Renderer* getRenderer(void);

		void createRenderer(std::string name, int width, int height, Uint32 flags);
		void destroy(void);

		void clearRenderer(Uint8 r, Uint8 g, Uint8 b);

		void drawToRenderer(SDL_Texture* texture, SDL_Rect location);
		void drawToRenderer(SDL_Texture* texture, SDL_Rect location, SDL_Rect frame);

		void putPixel(int x, int y, int r, int g, int b, int a);

		void drawText(std::string stringToDraw, TTF_Font *font, SDL_Color color, SDL_Rect location);
		void update(void);
};

#endif
