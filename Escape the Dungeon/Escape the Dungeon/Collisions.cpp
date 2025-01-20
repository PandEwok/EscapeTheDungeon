#include "Collisions.hpp"

vector<shared_ptr<Sprite>> toDeleteCoins = {};
vector<shared_ptr<Enemy>> toDeleteEnemies = {};

void collisionsProcess() {
	while (isGameRunning) {
		toDeleteCoins = {};
		for (shared_ptr<Sprite> coin : coinList) {
			if (coin) {
				if (coin->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds())) {
					toDeleteCoins.push_back(coin);
					playerScore++;
					cout << "score is now " << playerScore << greenString << " (+1)" << whiteString << endl;
				}
			}
		}
		for (shared_ptr<Sprite> coin : toDeleteCoins) {
			auto pos = find(coinList.begin(), coinList.end(), coin);
			coinList.erase(pos);
		}
		toDeleteEnemies = {};
		for (shared_ptr<Enemy> enemy : enemyList) {
			if (enemy) {
				if (enemy->getSprite()->getGlobalBounds().intersects(player.getSprite()->getGlobalBounds())) {
					toDeleteEnemies.push_back(enemy);
					continueAnimation(hpBar);
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
