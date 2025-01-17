#include "Game.hpp"


Player player;
Sprite background;

Game::Game() {
	player = Player();
	background.setTexture(backgroundTexture);
	background.setScale(0.8, 0.8);
}

void Game::update()
{
	
}
