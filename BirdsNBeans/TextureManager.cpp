#include "TextureManager.h"
#include "SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, NULL, flip);
}
void TextureManager::fillRect(SDL_Rect dest) {
	SDL_SetRenderDrawColor(Game::renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &dest);
}
