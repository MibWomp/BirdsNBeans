#pragma once
#include "Game.h"
#include <cmath>
class Seed : public Sprite {
private:
	bool isActive = true;
public:
	Seed(int x) : Sprite("assets/BirdsNBeans_Seed.png", x, 0) {
		spritePosition->velocity.y = 2;
	}
	void update() override {
		setCollisionToSpritePosition();
		//CREDITS TO PITA
		double angle = 10 * sin(0.002*(double)SDL_GetTicks());
		//std::cout << angle << std::endl;
		setAngle(angle);
		Sprite::update();
		//check if tile is hit
		//despawn if tile is hit or reach end of screen
	}
	void setInactive() {
		isActive = false;
	}
	bool getActive() {
		return isActive;
	}
};
