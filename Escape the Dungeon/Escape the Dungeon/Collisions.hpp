#pragma once

#include "Global.hpp"
#include "Game.hpp"

extern vector<shared_ptr<Sprite>> toDeleteCoins;
extern vector<shared_ptr<Enemy>> toDeleteEnemies;

void collisionsProcess();
