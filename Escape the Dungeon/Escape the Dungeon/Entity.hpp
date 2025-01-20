#pragma once

#include "Global.hpp"

class Entity {
protected:
	shared_ptr<Sprite> sprite = make_shared<Sprite>();
public:
	Entity(Vector2f textureSize);
	virtual void draw() = 0;
	shared_ptr<Sprite> getSprite();
};

class Player : public Entity {
protected:
	float speed = 4.f;
	int hp = 3;
	Clock framrate;
public:
	Player();
	void draw() override;
	float getSpeed();
	void move();
	Clock* getFramerate();
	int getHp();
	void decreaseHp(int value = 1);
};

class Enemy : public Entity {
protected:
	Clock framrate;
public:
	Enemy(Texture texture);
	Clock* getFramerate();
	void draw() override;
	virtual void move(Vector2f direction) = 0;
};

class ChaserEnemy : public Enemy {
public:
	ChaserEnemy();
	void move(Vector2f direction) override;
};