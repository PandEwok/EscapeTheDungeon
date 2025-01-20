// Escape the Dungeon.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Global.hpp"
#include "UserInput.hpp"
#include "Collisions.hpp"
#include "Entity.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;



int main() {
    srand(time(0));
    Image icon; icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    loadTextures();
    thread collisionsThread(collisionsProcess);
    collisionsThread.detach();
    thread uInputThread(userInput);
    uInputThread.detach();
    Event event;
    Clock mainClock;
    Game game;

    for (int i = 0; i < 10; i++) {
        shared_ptr<Sprite> newCoin = make_shared<Sprite>();
        newCoin->setTexture(coinTexture);
        newCoin->setTextureRect(IntRect(0, 0, coinTexture.getSize().y, coinTexture.getSize().y));
        newCoin->setOrigin(coinTexture.getSize().y / 2, coinTexture.getSize().y / 2);
        float randPosX = rand() % int(background.getGlobalBounds().getSize().x) - int(background.getGlobalBounds().getSize().x / 2);
        float randPosY = rand() % int(background.getGlobalBounds().getSize().y) - int(background.getGlobalBounds().getSize().y / 2);
        newCoin->setPosition(background.getPosition() + Vector2f(randPosX, randPosY)*0.8f);
        coinList.push_back(newCoin);
    }
    shared_ptr<ChaserEnemy> enemyTest = make_shared<ChaserEnemy>();
    enemyTest->getSprite()->setPosition(player.getSprite()->getPosition() + Vector2f(100,100));
    enemyList.push_back(enemyTest);

    while (isGameRunning) {
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
        for (shared_ptr<Sprite> coin : coinList) {
            if (coin) {
                window.draw(*coin);
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
    window.close(); exit(1);
}

