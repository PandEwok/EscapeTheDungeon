#include "Entity.hpp"


Entity::Entity(Vector2f textureSize) {
	sprite->setOrigin(textureSize / 2.f);
}

shared_ptr<Sprite> Entity::getSprite() {
	return sprite;
}

Player::Player() : Entity(Vector2f(playerTexture.getSize().y, playerTexture.getSize().y)) {
	sprite->setTexture(playerTexture);
	sprite->setTextureRect(IntRect(0, 0, playerTexture.getSize().y, playerTexture.getSize().y));
	sprite->setPosition(screenWidth / 2, screenHeight / 2); 
}

void Player::draw() {
	window.draw(*sprite);
}

float Player::getSpeed() {
	return speed;
}

void Player::move()
{
	sprite->move(inputMovement * timeSinceLastFrame.asSeconds() * speed);
}

Clock* Player::getFramerate()
{
	return &framrate;
}

int Player::getHp() {
	return hp;
}

void Player::decreaseHp(int value) {
	hp -= value;
}

Enemy::Enemy(Texture texture) : Entity(Vector2f(texture.getSize().y, texture.getSize().y)) {}

Clock* Enemy::getFramerate()
{
	return &framrate;
}

void Enemy::draw()
{
	window.draw(*sprite);
}

ChaserEnemy::ChaserEnemy() : Enemy(chaserEnemyTexture) {
	sprite->setTexture(chaserEnemyTexture);
	sprite->setTextureRect(IntRect(0, 0, chaserEnemyTexture.getSize().y, chaserEnemyTexture.getSize().y));
	sprite->setPosition(screenWidth / 2, screenHeight / 2);
}

void ChaserEnemy::move(Vector2f direction)
{
	sprite->move(80.f * direction * timeSinceLastFrame.asSeconds());
}
