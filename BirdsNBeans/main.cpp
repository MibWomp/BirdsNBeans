#include "Game.h"
Game* game = nullptr;
int main(int argc, char* argv[]) {
	game = new Game();
	const int FPS = 45;
	const int frameDelay = 1000 / FPS; //max time between frames

	Uint32 frameStart;
	int deltaTime;
	game->init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		deltaTime = SDL_GetTicks() - frameStart;

		if (frameDelay > deltaTime) { //if max time is being hit by deltaTime
			SDL_Delay(frameDelay - deltaTime); //then delay the program by the difference
		}

	}
	game->clean();
	return 0;
}