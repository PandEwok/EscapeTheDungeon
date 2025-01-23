// Escape the Dungeon.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Global.hpp"
#include "UserInput.hpp"
#include "Collisions.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Game.hpp"
#include "Tile.hpp"

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
    fstream map("Images/map1.txt");
    string line;
    Vector2f tilePosition = Vector2f(450, 100);
    while (true) {
        getline(map, line);
        if (line == ";") {
            break;
        }
        for (char tileChar : line) {
            if (tileChar == '0' or tileChar == '8' or tileChar == '9' or tileChar == 'o') {
                shared_ptr<Wall> newTile = make_shared<Wall>(tilePosition);
                if (tileChar == '8') {
                    newTile->getSprite()->setTexture(wallTileSideTexture);
                }
                else if (tileChar == '9') {
                    newTile->getSprite()->setTexture(wallTileSideTexture);
                    newTile->getSprite()->setScale(-1, 1);
                }
                else if (tileChar == 'o') {
                    newTile->getSprite()->setTexture(wallTileBackTexture);
                }
                tileMap.push_back(newTile);
            }
            else if (tileChar == '1') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
            }
            tilePosition.x += 16;
        }
        tilePosition.y += 16;
        tilePosition.x = 450;
    }
    
    Event event;
    Clock mainClock;

    Game game = newGame();

    thread collisionsThread(collisionsProcess);
    collisionsThread.detach();
    thread uInputThread(userInput);
    uInputThread.detach();

    Text gameOver;
    gameOver.setFont(mainFont);
    string gameOverMessage = "      GAME OVER\n-press escape to close-";
    gameOver.setString(gameOverMessage);
    gameOver.setCharacterSize(15);
    gameOver.setOrigin(Vector2f(90, 20));
    gameOver.setPosition(mainView.getCenter());

    while (isGameRunning) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
                cout << "close\n";
                /*isPauseMenu = true;*/
                isGameRunning = false;
            }
            else if (event.type == Event::Closed) { isGameRunning = false; }
        }
        if (player.getHp() <= 0) {
            gameOver.setPosition(mainView.getCenter());
            window.clear();

            window.draw(gameOver);

            window.display();
        }
        else {
            mainView.setCenter(player.getSprite()->getPosition());
            window.setView(mainView);

            timeSinceLastFrame = mainClock.restart();
            game.update();

            window.clear();

            for (shared_ptr<Tile> tile : tileMap) {
                window.draw(*tile->getSprite());
            }

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

