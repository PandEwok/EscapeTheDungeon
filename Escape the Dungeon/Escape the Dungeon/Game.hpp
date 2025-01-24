#pragma once

#include "Global.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Tile.hpp"

extern Player player;
extern Sprite background;
extern Text scoreText;

extern vector<shared_ptr<Enemy>> enemyList;
extern vector<shared_ptr<Coin>> coinList;
extern vector<shared_ptr<PotionHeal>> potionHealList;
extern vector<shared_ptr<Key>> keyList;
extern vector<shared_ptr<Tile>> tileMap;

class Game {
protected:
	Clock itemClock;
	Vector2f scroreTextOffset = Vector2f(35,80);
public:
	Game();
	void update();
};