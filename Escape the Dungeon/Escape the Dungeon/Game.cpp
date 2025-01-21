#include "Game.hpp"


Player player;
Sprite background;
Text scoreText;

vector<shared_ptr<Enemy>> enemyList;
vector<shared_ptr<Coin>> coinList;
vector<shared_ptr<PotionHeal>> potionHealList;

Game::Game() {
	player = Player();
	scoreText.setString("Coins | " + to_string(playerScore));
	scoreText.setFont(mainFont);
	scoreText.setCharacterSize(16);
	scoreText.setScale(Vector2f(0.8f,0.8f));
	scoreText.setPosition(mainView.getCenter()- scroreTextOffset);
	enemyList = {};
	coinList = {};
	potionHealList = {};
	background.setTexture(backgroundTexture);
	background.setOrigin(Vector2f(backgroundTexture.getSize()) / 2.f);
	background.setPosition(screenWidth / 2.f, screenHeight / 2.f);
	
	hpBar->setTexture(hpBarTexture);
	hpBar->setPosition(mainView.getCenter() + Vector2f(-90.f, 50.f));
	hpBar->setTextureRect(IntRect(0, 0, hpBarTexture.getSize().y, hpBarTexture.getSize().y));
}

void Game::update() {
	scoreText.setString("Coins | " + to_string(playerScore));
	scoreText.setPosition(mainView.getCenter() - scroreTextOffset);
	hpBar->setPosition(mainView.getCenter() + Vector2f(-90.f, 50.f));

	if (player.getFramerate()->getElapsedTime().asSeconds() >= 0.2f) {
		player.getFramerate()->restart();
		continueAnimation(player.getSprite());
	}
	if (itemClock.getElapsedTime().asSeconds() >= 0.18f) {
		itemClock.restart();
		for (shared_ptr<Coin> coin : coinList) {
			continueAnimation(coin->getSprite());
		}
		for (shared_ptr<PotionHeal> potion : potionHealList) {
			continueAnimation(potion->getSprite());
		}
	}
	for (shared_ptr<Enemy> enemy : enemyList) {
		if (enemy->getFramerate()->getElapsedTime().asSeconds() >= 0.18f) {
			enemy->getFramerate()->restart();
			continueAnimation(enemy->getSprite());
		}
		Vector2f direction = normalize(player.getSprite()->getPosition() - enemy->getSprite()->getPosition());
		direction = enemy->move(direction);
		if ((direction.x < 0.f and enemy->getSprite()->getScale().x > 0) or (direction.x > 0 and enemy->getSprite()->getScale().x < 0)) {
			enemy->getSprite()->setScale(enemy->getSprite()->getScale().x * (-1.f), enemy->getSprite()->getScale().y);
		}
	}

}
