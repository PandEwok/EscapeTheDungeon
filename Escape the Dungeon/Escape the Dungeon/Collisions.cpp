#include "Collisions.hpp"

vector<shared_ptr<Coin>> toDeleteCoins = {};
vector<shared_ptr<PotionHeal>> toDeletePotionHeal;
vector<shared_ptr<Enemy>> toDeleteEnemies = {};

void collisionsProcess() {
	while (isGameRunning) {

		// Coins
		toDeleteCoins = {};
		for (shared_ptr<Coin> coin : coinList) {
			if (coin) {
				if (coin->getSprite()->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds())) {
					toDeleteCoins.push_back(coin);
					coin->interact(player);
				}
			}
		}
		for (shared_ptr<Coin> coin : toDeleteCoins) {
			auto pos = find(coinList.begin(), coinList.end(), coin);
			coinList.erase(pos);
		}

		// Healing potions
		toDeletePotionHeal = {};
		for (shared_ptr<PotionHeal> potion : potionHealList) {
			if (potion) {
				if (potion->getSprite()->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds())) {
					toDeletePotionHeal.push_back(potion);
					potion->interact(player);
				}
			}
		}
		for (shared_ptr<PotionHeal> potion : toDeletePotionHeal) {
			auto pos = find(potionHealList.begin(), potionHealList.end(), potion);
			potionHealList.erase(pos);
		}

		// Enemies
		toDeleteEnemies = {};
		for (shared_ptr<Enemy> enemy : enemyList) {
			if (enemy) {
				if (enemy->getSprite()->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds())) {
					toDeleteEnemies.push_back(enemy);
					player.decreaseHp();
					cout << "HP is now " << player.getHp() << redString << " (-1)" << whiteString << endl;
				}
			}
		}
		for (shared_ptr<Enemy> enemy : toDeleteEnemies) {
			auto pos = find(enemyList.begin(), enemyList.end(), enemy);
			enemyList.erase(pos);
		}
	}
}
