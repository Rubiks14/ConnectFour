#include "../hdr/Texture.h"

Texture::Texture(void) {
}

Texture::Texture(const std::string fileName, SDL_Renderer* renderer) {
	loadFromFile(fileName, renderer);
}

Texture::~Texture(void) {
	destroy();
}

void Texture::setXPosition(int x){
	locationAndSize.x = x;
}

void Texture::setYPosition(int y){
	locationAndSize.y = y;
}

SDL_Rect Texture::getLocation(){
	return locationAndSize;
}

SDL_Texture* Texture::getTexture(void) {
	return textureImage;
}

bool Texture::loadFromFile(const std::string fileName, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
	bool loaded;
	if (tempSurface == NULL) {
		std::cerr << "Surface Error: " << IMG_GetError();
		loaded = false;
	} else {
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0, 0xFF));

		textureImage = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (textureImage == NULL) {
			std::cerr << "Texture Error: " << SDL_GetError();
			SDL_FreeSurface(tempSurface);
			loaded = false;
		}
		locationAndSize.w = tempSurface->w;
		locationAndSize.h = tempSurface->h;
		SDL_FreeSurface(tempSurface);
		loaded = true;
	}
	return loaded;
}

void Texture::destroy(void) {
	SDL_DestroyTexture(textureImage);
	textureImage = NULL;
}


