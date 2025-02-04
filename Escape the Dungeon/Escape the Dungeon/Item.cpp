#include "Item.hpp"

Coin::Coin() : Entity(Vector2f(coinTexture.getSize().y, coinTexture.getSize().y)) {
	sprite->setTexture(coinTexture);
	sprite->setTextureRect(IntRect(0, 0, coinTexture.getSize().y, coinTexture.getSize().y));
}

void Coin::interact(Player& player)
{
	playerScore++;
	cout << "score is now " << playerScore << greenString << " (+1)" << whiteString << endl;
}

void Coin::draw()
{
	window.draw(*sprite);
}

PotionHeal::PotionHeal() : Entity(Vector2f(potionHealTexture.getSize().y, potionHealTexture.getSize().y)) {
	sprite->setTexture(potionHealTexture);
	sprite->setTextureRect(IntRect(0, 0, potionHealTexture.getSize().y, potionHealTexture.getSize().y));
}

void PotionHeal::interact(Player& player)
{
	player.increaseHp();
}

void PotionHeal::draw()
{
	window.draw(*sprite);
}

Key::Key() : Entity(Vector2f(keyTexture.getSize().y, keyTexture.getSize().y))
{
	sprite->setTexture(keyTexture);
	sprite->setTextureRect(IntRect(0, 0, keyTexture.getSize().y, keyTexture.getSize().y));
}

void Key::interact(Player& player)
{
	player.setKeyState(player.getKeyState()+1);
}

void Key::draw()
{
	window.draw(*sprite);
}
