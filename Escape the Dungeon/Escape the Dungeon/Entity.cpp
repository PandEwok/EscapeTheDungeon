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
	sprite->setPosition(10,10);
}

void Player::draw() {
	window.draw(*sprite);
}

float Player::getSpeed() {
	return speed;
}

void Player::move()
{
	sprite->move(inputMovement * timeSinceLastFrameInputs.asSeconds() * speed);
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

int Player::getKeyState()
{
	return keyNumber;
}

void Player::setKeyState(int newValue)
{
	keyNumber = newValue;
}

FloatRect Player::getHitBox() {
	Vector2f boundsPos = sprite->getGlobalBounds().getPosition();
	Vector2f boundsSize = sprite->getGlobalBounds().getSize();
	return FloatRect(boundsPos.x + boundsSize.x/3.f, boundsPos.y + boundsSize.y/3.f, boundsSize.x/3.f, boundsSize.y/3.f*2);
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
	if ((currentPoint == path.size() - 1 or currentPoint < previousPoint) and currentPoint != 0) {
		nextPoint = currentPoint-1;
	}
	else {
		nextPoint = currentPoint + 1;
	}
	direction = normalize(path[nextPoint] - sprite->getPosition());
	sprite->move(65.f * direction * timeSinceLastFrame.asSeconds());
	if ((int(sprite->getPosition().x) >= int(path[nextPoint].x - 1) and int(sprite->getPosition().x) <= int(path[nextPoint].x + 1)) and
		(int(sprite->getPosition().y) >= int(path[nextPoint].y - 1) and int(sprite->getPosition().y) <= int(path[nextPoint].y + 1))) {
		previousPoint = currentPoint;
		currentPoint = nextPoint;
	}
	return direction;
}
