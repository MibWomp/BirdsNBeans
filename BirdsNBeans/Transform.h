#pragma once
#include "Vector2D.h"
#include "Game.h"
class Transform {
public:
	Vector2D position;
	Vector2D velocity;
	int speed;
	Transform() {
		position.x = 0.0f;
		position.y = 0.0f;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		speed = 1;
	}
	Transform(float positionX, float positionY, int speedInput) {
		position.x = positionX;
		position.y = positionY;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		speed = speedInput;
	}
	void update() {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};