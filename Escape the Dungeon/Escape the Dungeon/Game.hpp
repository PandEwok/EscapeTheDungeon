#pragma once

#include "Global.hpp"
#include "Entity.hpp"

extern Player player;
extern Sprite background;
extern Text scoreText;
extern shared_ptr<Sprite> hpBar;

extern vector<shared_ptr<Enemy>> enemyList;

class Game {
protected:
	Clock coinClock;
	Vector2f scroreTextOffset = Vector2f(35,80);
public:
	Game();
	void update();
};