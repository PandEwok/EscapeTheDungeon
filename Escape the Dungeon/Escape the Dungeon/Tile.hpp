#pragma once

#include "Global.hpp"

class Tile {
protected:
	shared_ptr<Sprite> sprite = make_shared<Sprite>();
	string type;
public:
	shared_ptr<Sprite> getSprite();
	Tile(Vector2f position);
	string getType();
};

class Wall : public Tile {
public:
	Wall(Vector2f position);
};

class Floor : public Tile {
public:
	Floor(Vector2f position);
};

class Door : public Tile {
public:
	Door(Vector2f position);
};

class Flag : public Tile {
public:
	Flag(Vector2f position);
};

class Candle : public Tile {
public:
	Candle(Vector2f position);
};