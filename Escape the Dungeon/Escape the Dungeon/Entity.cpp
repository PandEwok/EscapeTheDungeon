#include "Entity.hpp"


Entity::Entity(Texture texture) {
	sprite.setOrigin(Vector2f(texture.getSize()) / 2.f);
}

Sprite* Entity::getSprite() {
	return &sprite;
}

Player::Player() : Entity(playerTexture) {
	sprite.setTexture(playerTexture);
	sprite.setPosition(screenWidth / 2, screenHeight / 2);
	sprite.setScale(2, 2);
}

void Player::draw() {
	window.draw(sprite);
}

float Player::getSpeed() {
	return speed;
}

void Player::move()
{
	sprite.move(inputMovement * timeSinceLastFrame.asSeconds() * speed);
}

