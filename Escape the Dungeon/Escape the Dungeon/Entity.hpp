#pragma once

#include "Global.hpp"

class Entity {
protected:
	Sprite sprite;
public:
	Entity(Texture texture);
	virtual void draw() = 0;
	Sprite* getSprite();
};

class Player : public Entity {
protected:
	float speed = 4.f;
	int hp = 3;
public:
	Player();
	void draw() override;
	float getSpeed();
	void move();
};