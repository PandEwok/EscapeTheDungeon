#pragma once

#include "Global.hpp"
#include "Entity.hpp"

extern Player player;
extern Sprite background;

class Game {
public:
	Game();
	void update();
};