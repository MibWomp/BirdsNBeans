#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <random>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);
	void handleEvents();
	void update();
	void render();
	
	void clean();

	bool running() { return isRunning; };

	float getRng(float low, float high) {
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	};

	int getIntRng(int low, int high) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> distrib(low, high);

		return distrib(rng);
	};

	static SDL_Renderer* renderer;
	static SDL_Event event;
	


private:
	bool isRunning;
	SDL_Window* window;


};

