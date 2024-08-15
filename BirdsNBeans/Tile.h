#pragma once
#include "Sprite.h"
class Tile : public Sprite {
private:
	bool destroyed = false;

public:
	Tile() = default;
	Tile(int tileNum) : Sprite("assets/BirdsNBeans_Tile.png", tileNum*64.0 , 576.0) {
	
	}
	void setDestroyed() { //SET TO DESTROY SETTINGS
		destroyed = true;
		setInvisible(destroyed);
		Sprite::setCollision(destRect.x, 512.0); //collision for player
	}
	bool getDestroyed() { //RETURN IF DESTROYED
		return destroyed;
	}
	void reset() {	 //RESET TO UNDESTORYED
		destroyed = false;
		setInvisible(destroyed);
		Sprite::setCollision(destRect.x, 576.0);
	}

	void setInvisible(bool invisible) {
		if (invisible) {
			srcRect.w = srcRect.h = 0;
		}
		else {
			srcRect.w = srcRect.h = 16;
		}
	}

	void update() override {
		
	}

};
