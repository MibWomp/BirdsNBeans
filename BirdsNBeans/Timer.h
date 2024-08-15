#pragma once
class Timer {
public:
	Timer() = default;

	void start() { 
		startTicks = SDL_GetTicks();
	};

	Uint32 getTicks() { //in milliseconds
		return SDL_GetTicks() - startTicks;
	};

private:

	Uint32 startTicks;

};