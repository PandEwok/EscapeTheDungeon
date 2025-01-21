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
	continueAnimation(hpBar);
	hp -= value;
}

void Player::increaseHp(int value)
{
	if (hp < 3) {
		for (int i = 0; i < 3; i++) {
			continueAnimation(hpBar);
		}
		hp += value;
		cout << "HP is now " << hp << greenString << " (+1)" << whiteString << endl;
	}
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
}

Vector2f ChaserEnemy::move(Vector2f direction)
{
	sprite->move(80.f * direction * timeSinceLastFrame.asSeconds());
	return direction;
}

PatrollingEnemy::PatrollingEnemy(vector<Vector2f> _path) : Enemy(patrollingEnemyTexture) {
	path = _path;
	sprite->setTexture(patrollingEnemyTexture);
	sprite->setTextureRect(IntRect(0, 0, patrollingEnemyTexture.getSize().y, patrollingEnemyTexture.getSize().y));
	sprite->setPosition(path[0]);
}

Vector2f PatrollingEnemy::move(Vector2f direction)
{
	int nextPoint;
	if (currentPoint == path.size() - 1) {
		nextPoint = 0;
	}
	else {
		nextPoint = currentPoint + 1;
	}
	direction = normalize(path[nextPoint] - sprite->getPosition());
	sprite->move(65.f * direction * timeSinceLastFrame.asSeconds());
	if (int(sprite->getPosition().x) == int(path[nextPoint].x - 1) or int(sprite->getPosition().x) == int(path[nextPoint].x + 1)) {
		currentPoint = nextPoint;
	}
	return direction;
}
