#pragma once

#include "Global.hpp"
#include "Game.hpp"

extern vector<shared_ptr<Coin>> toDeleteCoins;
extern vector<shared_ptr<PotionHeal>> toDeletePotionHeal;
extern vector<shared_ptr<Key>> toDeleteKeys;
extern vector<shared_ptr<Enemy>> toDeleteEnemies;

void collisionsProcess();
