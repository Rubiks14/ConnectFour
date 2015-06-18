#include "../hdr/Renderer.h"

Renderer::Renderer(void) {
}

Renderer::Renderer(std::string name, int width, int height, Uint32 flags) {
	createRenderer(name, width, height, flags);
}

Renderer::~Renderer(void) {
	destroy();
}

SDL_Renderer* Renderer::getRenderer(void) {
	return renderer;
}

void Renderer::createRenderer(std::string name, int width, int height, Uint32 flags) {
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
	renderFrame = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	screenSize = {0, 0, width, height};
	TTF_Init();
}

void Renderer::destroy(void) {
    SDL_DestroyTexture(renderFrame);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Renderer::clearRenderer(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderTarget(renderer, renderFrame);
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderClear(renderer);
}

void Renderer::update(void) {
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, renderFrame, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Renderer::drawToRenderer(SDL_Texture* texture, SDL_Rect location) {
    SDL_SetRenderTarget(renderer, renderFrame);
	SDL_RenderCopy(renderer, texture, NULL, &location);
}
void Renderer::drawToRenderer(SDL_Texture* texture, SDL_Rect location, SDL_Rect frame) {
    SDL_SetRenderTarget(renderer, renderFrame);
	SDL_RenderCopy(renderer, texture, &frame, &location);
}

void Renderer::putPixel(int x, int y, int r, int g, int b, int a){
    SDL_SetRenderTarget(renderer, renderFrame);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void Renderer::drawText(std::string stringToDraw, TTF_Font *font, SDL_Color color, SDL_Rect location){
	SDL_Surface *text = TTF_RenderText_Solid(font, stringToDraw.c_str(), color);
	SDL_Texture *textSurface = SDL_CreateTextureFromSurface(getRenderer(), text);
	SDL_FreeSurface(text);
	drawToRenderer(textSurface, location);
	SDL_DestroyTexture(textSurface);
}
