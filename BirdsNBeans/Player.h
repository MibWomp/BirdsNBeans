#pragma once
#include "Sprite.h"
#include <vector>
#include "Game.h"
#include "Tongue.h"
class Player : public Sprite {
private:
	int currFrame = -1; //if current frame is -1, then not in animation
	enum Animations { idle, walkLeft, walkRight, tongueOut, tongueIn, eat };
	const Uint8* currentKeyStates;
	bool spacePressed = false;
	bool isLeft = true;
	bool hit = false;
	SDL_Rect spriteClip[3];
	bool animationReady = true;
public:
	Tongue tongue;
	Animations currAnimation;
	Animations animationCache = idle;

	Player() = default;

	Player(const char* filePath) : Sprite(filePath, 448, 512) {
		currAnimation = idle;
		tongue = Tongue(spritePosition->position.x, spritePosition->position.y);
		//USED FOR SPRITESHEET SRCRECT
		spriteClip[0].x = spriteClip[0].y = spriteClip[1].y = spriteClip[2].y = 0;
		spriteClip[1].x = 16;
		spriteClip[2].x = 32;
		spriteClip[0].w = spriteClip[0].h = spriteClip[1].h = spriteClip[1].w = spriteClip[2].w = spriteClip[2].h = 16;

	}


	void update() override { 	
		std::cout << "currAnimation is " << currAnimation<< std::endl;
		setCollisionToSpritePosition();
		handleAnimation();
		Sprite::update();
		if (isLeft) {
			tongue.update(spritePosition->position.x + 64, spritePosition->position.y + 64, spacePressed, true);
		}
		else {
			tongue.update(spritePosition->position.x, spritePosition->position.y+64, spacePressed, false);
		}
		(true);
		
	}

	bool wallCollision() {
		if (spritePosition->position.x < 0 || spritePosition->position.x>960) {
			return true;
		}
		return false;
	}
	void setAnimationReady(bool tof) {
		animationReady = tof;
	}

	void handleControls() { //CALLED IN GAME.CPP
		currentKeyStates = SDL_GetKeyboardState(NULL);
		animationCache = currAnimation;
		std::cout << "got hit" << tongue.getHit() << std::endl;
		if (!currentKeyStates[SDL_SCANCODE_SPACE]) {
			spacePressed = false;
		}
		if (currAnimation == tongueOut && !currentKeyStates[SDL_SCANCODE_SPACE]) { //RETRACT MID TONGUE
			if (tongue.getTongueCounter() == 0) { 
				currAnimation = idle;
			}
			currAnimation = tongueIn;
		}
		else if (tongue.getHit() && tongue.getTongueCounter() == 0) {
			currAnimation = eat;
			tongue.setHit(false);
		}
		else if (currAnimation == idle && currentKeyStates[SDL_SCANCODE_SPACE]) { // START TONGUE
			spacePressed = true;
			currAnimation = tongueOut;
		}
		else if (currAnimation == tongueIn && tongue.getTongueCounter() == 0) { // STOP TONGUE
			currAnimation = idle;
			tongue.setHit(false);
		}
		else if (currAnimation == idle && currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D]) { // BOTH KEYS PRESSED
			//currAnimation = animationCache;
			//std::cout << "both" << std::endl;
		}
		else if (currAnimation == idle && currentKeyStates[SDL_SCANCODE_A]) { // LEFT PRESSED
			std::cout << "left" << std::endl;
			isLeft = true;
			currAnimation = walkLeft;
		}
		else if (currAnimation == idle && currentKeyStates[SDL_SCANCODE_D]){ //RIGHT PRESSED
			isLeft = false;
			//std::cout << "right" << std::endl;
			currAnimation = walkRight;
		}
		else if (currAnimation != idle && currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D]) { //BOTH PRESSED MID WALK
			//std::cout << "both2" << std::endl;
			//do nothing
		}
		else {
			//SEEMS TO REACH HERE MID WALKING ANIMATION
			//currAnimation = idle;
			//std::cout << "not in" << std::endl;
		}
	}
	
	void handleAnimation(){
			switch(currAnimation) {
			case idle:
				setIdle();
				srcRect = spriteClip[0];
				break;
			case walkLeft: 
				srcRect = spriteClip[0];
				handleWalk();
				break;
			case walkRight:
				srcRect = spriteClip[0];
				handleWalk();
				break;
			case tongueOut:
				srcRect = spriteClip[2];
				break;
			case tongueIn:
				srcRect = spriteClip[2];
				break;
			case eat:
				handleEat();
				break;
			default:
				break;
			}
	}

	void setIdle() {
		tongue.resetTongue(spritePosition->position.x, spritePosition->position.y);
		currFrame = -1;
		animationCache = idle;
		currAnimation = idle;
	}
	
	void handleWalk() { //animate walks left and right
		if (currFrame == -1) {
			currFrame = 0;
		}
		switch (currFrame) {
		case 0: // on frame 0
			std::cout << "case 0" << std::endl;
			spritePosition->velocity.y = -4;
			if (currAnimation == walkLeft) {
				setFlip(SDL_FLIP_NONE);
				spritePosition->velocity.x = -4;
			}
			if (currAnimation == walkRight) {
				setFlip(SDL_FLIP_HORIZONTAL);
				spritePosition->velocity.x = 4;
			}
			currFrame++;
			break;
		case 1:
			std::cout << "case 1" << std::endl;
			spritePosition->velocity.y = 4;
			if (currAnimation == walkLeft) {
				spritePosition->velocity.x = -4;
			}
			if (currAnimation == walkRight) {
				spritePosition->velocity.x = 4;
			}
			currFrame++;
			break;
		case 2:
			std::cout << "case 2" << std::endl;
			spritePosition->velocity.x = 0;
			spritePosition->velocity.y = 0;
			currAnimation = idle;
			currFrame = -1;
			break;
		default:
			break;
		}
	}
	void handleEat() {
		if (currFrame == -1) {
			currFrame = 0;
		}
		switch (currFrame) {
		case 0: case 2: case 4:
			srcRect = spriteClip[1];
			break;
		case 1: case 3: case 7:
			srcRect = spriteClip[0];
			break;
		case 8:
			setIdle();
			currFrame = -2;
			break;
		}
		currFrame++;
	}
};
