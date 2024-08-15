#pragma once
#include "Sprite.h"


//tiles are 64*64. src is 16x16 per "tile" upscaled 4x. srcrect must grow up to total w/h of 160. destrect scaled to x4 that so 640.
class Tongue : public Sprite{
private:
	int tongueCounter;
	bool retract = false;
	bool active = false;
	bool hit = false;
public:

	Tongue() = default;
	Tongue(int xPos, int yPos) : Sprite("Assets/BirdsNBeans_Tongue.png", xPos, yPos) {
		tongueCounter = 0;
		srcRect.w = srcRect.h = 0;
		setCollision(xPos, yPos);
	}

	void update(int posX, int posY, bool tongueBool, bool isLeft) {
		std::cout << "tongue counter:" << tongueCounter << std::endl;
	//	std::cout << "position:"<< spritePosition->position.x << "," << spritePosition->position.y<<std::endl;

		if (wallCollision() || hit) { //UPDATE TONGUE POSITION
			retract = true;
		}
		if (!retract && tongueBool && tongueCounter <= 40) {
			if (!(tongueCounter == 40)) {
				tongueCounter++;
			}
			updateActiveTongue(posX, posY, tongueBool, isLeft);
		}
		else if (tongueCounter > 0) {
			tongueCounter--;
			updateActiveTongue(posX, posY, false, isLeft);
		}
		else {
			spritePosition->position.x = posX;
			spritePosition->position.y = posY;
		}
		TextureManager::fillRect(collision);
		//std::cout << destRect.w << "," << destRect.h << std::endl;
		Sprite::update();
		//std::cout << destRect.w << "," << destRect.h << std::endl;
		if (isLeft) {
			setFlip(SDL_FLIP_NONE);
		}
		else {
			setFlip(SDL_FLIP_HORIZONTAL);
		}

	}

	void setHit(bool hitt) { //WHEN A SEED IS HIT
		hit = hitt;
	}
	bool getHit() {
		return hit;
	}
	void resetTongue(int posX, int posY) {
		spritePosition->position.x = posX;
		spritePosition->position.y = posY;
	}
	int getTongueCounter() {
		return tongueCounter;
	}
	bool getActive() {
		return active;
	}

	bool wallCollision() {
		if (collision.x <= 0 || collision.x >= 960 || collision.y < 0 ) {
			return true;
		}
		return false;
	}

	void updateActiveTongue(int posX, int posY, bool isIncreasing, bool isLeft) {
		//std::cout<<"passed posx and posy:" <<posX<<","<<posY<<std::endl;
		
		if (isIncreasing) {
			active = true;
			spritePosition->position.y = posY - tongueCounter * 16 - 16;
			if (isLeft) {
				spritePosition->position.x = posX - tongueCounter*16 -32;
				collision.x = spritePosition->position.x;
			}
			else {
				spritePosition->position.x = posX + 32;
				collision.x = posX + tongueCounter*16 - 64;
			}
			collision.y = spritePosition->position.y;
			srcRect.w = tongueCounter * 4 ;
			srcRect.h = tongueCounter * 4 ;
			destRect.w = tongueCounter * 16;
			destRect.h = tongueCounter * 16;

		}
		else {
			active = false;
			if (isLeft) {
				spritePosition->position.x = posX - tongueCounter * 16 - 32;

			}
			spritePosition->position.y = posY - tongueCounter * 16 - 16;
			collision.x = posX;
			collision.y = posY;
			srcRect.w = tongueCounter * 4;
			srcRect.h = tongueCounter * 4;
			destRect.w = tongueCounter * 16;
			destRect.h = tongueCounter * 16;
		}

		if (tongueCounter == 0) { //PREVENTS GLITCHING DURING COLLISION
			
			retract = false;
		}
	}
	

};