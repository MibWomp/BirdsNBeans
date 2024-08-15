#pragma once
#include "Transform.h"
#include "TextureManager.h"

/*
	MUST IMPLEMENT: 
	TONGUE
	destRect WITH TILES AND MAP
	
*/
class Sprite
{
protected:
	SDL_Rect srcRect;
	SDL_RendererFlip renderFlip = SDL_FLIP_NONE;
	double angle;

public:
	SDL_Rect collision;
	SDL_Rect destRect;
	SDL_Texture* spriteTexture;
	Transform* spritePosition;
	Sprite() = default;
	Sprite(const char* filePath, double xPos, double yPos) {
		setTexture(filePath);
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 16; //source is 16x16
		destRect.x = collision.x = xPos; ///initialized
		destRect.y = collision.y = yPos;
		destRect.w = destRect.h = collision.w = collision. h = 64; //render to 64x64 so 4x
		spritePosition = new Transform(xPos, yPos, 1);
		angle = 0.0;
		std::cout << "initialized" << std::endl;
	}
	void setCollision(double xPos, double yPos) {
		collision.x = xPos;
		collision.y = yPos;
	}
	void setCollisionToSpritePosition() {
		collision.x = spritePosition->position.x;
		collision.y = spritePosition->position.y;
	}
	void setTexture(const char* filePath) {
		spriteTexture = TextureManager::LoadTexture(filePath);
	};
	void setAngle(double ang) {
		angle = ang;
	}
	void setFlip(SDL_RendererFlip flip) {
		renderFlip = flip;
	}
	virtual void update() {
		spritePosition->update();
		destRect.x = (int)spritePosition->position.x;
		destRect.y = (int)spritePosition->position.y;
	}
	void draw() {
		TextureManager::Draw(spriteTexture, srcRect, destRect, angle, renderFlip);
	};

	bool checkCollision(SDL_Rect collisionBox) { //check is THIS is colliding with B
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = this->collision.x;
		leftB = collisionBox.x;
		
		rightA = this->collision.x + this->collision.w;
		rightB = collisionBox.x + collisionBox.w;

		topA = this->collision.y;
		topB = collisionBox.y;

		bottomA = this->collision.y + this->collision.h;
		bottomB = collisionBox.y + collisionBox.h;

		if (bottomA <= topB) {
			return false;
		}
		if (topA >= bottomB) {
			return false;
		}
		if (rightA <= leftB) {
			return false;
		}
		if (leftA >= rightB) {
			return false;
		}
		return true;
	}
	//position
	//texture
	//destRect

};

