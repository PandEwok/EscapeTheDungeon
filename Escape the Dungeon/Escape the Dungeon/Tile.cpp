#include "Tile.hpp"

shared_ptr<Sprite> Tile::getSprite()
{
	return sprite;
}

Tile::Tile(Vector2f position)
{
	//sprite->setTextureRect(IntRect(0, 0, 16, 16));
	sprite->setPosition(position);
}

string Tile::getType()
{
	return type;
}

Wall::Wall(Vector2f position) : Tile(position) {
	sprite->setTexture(wallTileTexture);
	type = "Wall";
}

Floor::Floor(Vector2f position) : Tile(position)
{
	sprite->setTexture(floorTileTexture);
	type = "Floor";
}
