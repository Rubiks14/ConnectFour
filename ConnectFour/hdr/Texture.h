#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Texture {
	private:
		// no private data members
	protected:
		SDL_Rect locationAndSize;
		SDL_Texture* textureImage;
	public:
		Texture(void);
		Texture(const std::string fileName, SDL_Renderer* renderer);
		~Texture(void);

		void setXPosition(int x);
		void setYPosition(int y);
		SDL_Rect getLocation();
		SDL_Texture* getTexture(void);

		bool loadFromFile(const std::string fileName, SDL_Renderer* renderer);

		void destroy(void);
};

#endif
