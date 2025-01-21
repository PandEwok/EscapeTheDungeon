// Escape the Dungeon.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Global.hpp"
#include "UserInput.hpp"
#include "Collisions.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;


Game newGame() {
    Game game;

    for (int i = 0; i < 10; i++) {
        shared_ptr<Coin> newCoin = make_shared<Coin>();
        shared_ptr<Sprite> sprite = newCoin->getSprite();
        float randPosX = rand() % int(background.getGlobalBounds().getSize().x) - int(background.getGlobalBounds().getSize().x / 2);
        float randPosY = rand() % int(background.getGlobalBounds().getSize().y) - int(background.getGlobalBounds().getSize().y / 2);
        sprite->setPosition(background.getPosition() + Vector2f(randPosX, randPosY) * 0.8f);
        coinList.push_back(newCoin);
    }
    for (int i = 0; i < 5; i++) {
        shared_ptr<PotionHeal> newPotion = make_shared<PotionHeal>();
        shared_ptr<Sprite> sprite = newPotion->getSprite();
        float randPosX = rand() % int(background.getGlobalBounds().getSize().x) - int(background.getGlobalBounds().getSize().x / 2);
        float randPosY = rand() % int(background.getGlobalBounds().getSize().y) - int(background.getGlobalBounds().getSize().y / 2);
        sprite->setPosition(background.getPosition() + Vector2f(randPosX, randPosY) * 0.8f);
        potionHealList.push_back(newPotion);
    }
    for (int i = 0; i < 2; i++) {
        shared_ptr<ChaserEnemy> enemyTest = make_shared<ChaserEnemy>();
        float randPosX = rand() % int(background.getGlobalBounds().getSize().x) - int(background.getGlobalBounds().getSize().x / 2);
        float randPosY = rand() % int(background.getGlobalBounds().getSize().y) - int(background.getGlobalBounds().getSize().y / 2);
        enemyTest->getSprite()->setPosition(background.getPosition() + Vector2f(randPosX, randPosY) * 0.8f);
        enemyList.push_back(enemyTest);
    }
    vector<Vector2f> path = { Vector2f(player.getSprite()->getPosition()) + Vector2f(-120, -170), Vector2f(player.getSprite()->getPosition()) + Vector2f(120, -170) };
    shared_ptr<PatrollingEnemy> enemyTest2 = make_shared<PatrollingEnemy>(path);
    enemyList.push_back(enemyTest2);

    return game;
}


int main() {
    srand(time(0));
    Image icon; icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    loadTextures();
    
    Event event;
    Clock mainClock;

    Game game = newGame();

    thread collisionsThread(collisionsProcess);
    collisionsThread.detach();
    thread uInputThread(userInput);
    uInputThread.detach();

    Text gameOver;
    gameOver.setFont(mainFont);
    gameOver.setString("GAME OVER\n-press escape to close-");
    gameOver.setPosition(mainView.getCenter());

    while (isGameRunning) {
        if (player.getHp() <= 0) {
            window.clear();

            window.draw(gameOver);

            window.display();
        }
        else {
            mainView.setCenter(player.getSprite()->getPosition());
            window.setView(mainView);

            timeSinceLastFrame = mainClock.restart();
            game.update();

            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
                    cout << "close\n";
                    /*isPauseMenu = true;*/
                    isGameRunning = false;
                }
                else if (event.type == Event::Closed) { isGameRunning = false; }
            }
            window.clear();

            window.draw(background);
            for (shared_ptr<Coin> coin : coinList) {
                if (coin) {
                    coin->draw();
                }
            }
            for (shared_ptr<PotionHeal> potion : potionHealList) {
                if (potion) {
                    potion->draw();
                }
            }
            player.draw();
            for (shared_ptr<Enemy> enemy : enemyList) {
                if (enemy) {
                    enemy->draw();
                }
            }
            window.draw(*hpBar);
            window.draw(scoreText);

            window.display();
        }
    }
    window.close(); exit(1);
}

