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

    for (int i = 0; i < 2; i++) {
        shared_ptr<ChaserEnemy> enemyTest = make_shared<ChaserEnemy>();
        float randPosX = rand() % int(background.getGlobalBounds().getSize().x) - int(background.getGlobalBounds().getSize().x / 2);
        float randPosY = rand() % int(background.getGlobalBounds().getSize().y) - int(background.getGlobalBounds().getSize().y / 2);
        enemyTest->getSprite()->setPosition(background.getPosition() + Vector2f(randPosX, randPosY) * 0.8f);
        enemyList.push_back(enemyTest);
    }
    

    return game;
}


int main() {
    srand(time(0));
    Image icon; icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    loadTextures();
    Game game = newGame();
    float chrono = 60;
    Clock gameTime;
    Text chronoText;
    chronoText.setFont(mainFont);
    chronoText.setCharacterSize(14);
    vector<Vector2f> path1 = {};
    vector<Vector2f> path2 = {};

    fstream map("Images/map1.txt");
    string line;
    Vector2f tilePosition = Vector2f(0, 0);
    while (true) {
        getline(map, line);
        if (line == ";") {
            break;
        }
        for (char tileChar : line) {
            if (tileChar == '0' or tileChar == '8' or tileChar == '9' or tileChar == 'o' or tileChar == '6' or tileChar == '7' or tileChar == 'u'
                or tileChar == 'q' or tileChar == 'p' or tileChar == 'f' or tileChar == 'g' or tileChar == 'e' or tileChar == 'a' or tileChar == 'F') {
                shared_ptr<Wall> newTile = make_shared<Wall>(tilePosition);
                if (tileChar == '8') {
                    newTile->getSprite()->setTexture(wallTileSideTexture);
                }
                else if (tileChar == '9') {
                    newTile->getSprite()->setTexture(wallTileSideTexture);
                    newTile->getSprite()->setScale(-1, 1);
                    newTile->getSprite()->move(Vector2f(16, 0));
                }
                else if (tileChar == 'o') {
                    newTile->getSprite()->setTexture(wallTileBackTexture);
                }
                else if (tileChar == '6') {
                    newTile->getSprite()->setTexture(wallTileMiddleTexture);
                }
                else if (tileChar == 'u') {
                    newTile->getSprite()->setTexture(wallTileMiddleEndTexture);
                }
                else if (tileChar == '7') {
                    newTile->getSprite()->setTexture(wallTileIntersectionTexture);
                }
                else if (tileChar == 'q') {
                    newTile->getSprite()->setTexture(wallTileIntersectionSideTexture);
                }
                else if (tileChar == 'p') {
                    newTile->getSprite()->setTexture(wallTileIntersectionSideTexture);
                    newTile->getSprite()->setScale(-1, 1);
                    newTile->getSprite()->move(Vector2f(16, 0));
                }
                else if (tileChar == 'f') {
                    newTile->getSprite()->setTexture(wallTileBackIntersectionTexture);
                }
                else if (tileChar == 'g') {
                    newTile->getSprite()->setTexture(wallTileBackIntersectionTexture);
                    newTile->getSprite()->setScale(-1, 1);
                    newTile->getSprite()->move(Vector2f(16, 0));
                }
                else if (tileChar == 'e') {
                    newTile->getSprite()->setTexture(wallTileBackEndTexture);
                }
                else if (tileChar == 'a') {
                    newTile->getSprite()->setTexture(wallTileBackEndTexture);
                    newTile->getSprite()->setScale(-1, 1);
                    newTile->getSprite()->move(Vector2f(16, 0));
                }
                tileMap.push_back(newTile);
                if (tileChar == 'F') {
                    shared_ptr<Flag> newFlag = make_shared<Flag>(tilePosition);
                    tileMap.push_back(newFlag);
                }
            }
            else if (tileChar == '1') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                float coinRand = rand() % 100;
                if (coinRand < 1) {
                    shared_ptr<Coin> newCoin = make_shared<Coin>();
                    newCoin->getSprite()->setPosition(tilePosition + Vector2f(8, 8));
                    coinList.push_back(newCoin);
                }
            }
            else if (tileChar == 'k') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                shared_ptr<Key> newKey = make_shared<Key>();
                newKey->getSprite()->setPosition(tilePosition + Vector2f(8,8));
                keyList.push_back(newKey);
            }
            else if (tileChar == '&') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                shared_ptr<PotionHeal> newPotion = make_shared<PotionHeal>();
                newPotion->getSprite()->setPosition(tilePosition + Vector2f(8, 8));
                potionHealList.push_back(newPotion);
            }
            else if (tileChar == 'c') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                shared_ptr<Coin> newCoin = make_shared<Coin>();
                newCoin->getSprite()->setPosition(tilePosition + Vector2f(8, 8));
                coinList.push_back(newCoin);
            }
            else if (tileChar == '$') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                player.getSprite()->setPosition(tilePosition + Vector2f(8, 8));
            }
            else if (tileChar == 'I') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                shared_ptr<Candle> newCandle = make_shared<Candle>(tilePosition);
                tileMap.push_back(newCandle);
            }
            else if (tileChar == 's') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                path1.push_back(tilePosition + Vector2f(8, 8));
            }
            else if (tileChar == 't') {
                shared_ptr<Floor> newTile = make_shared<Floor>(tilePosition);
                tileMap.push_back(newTile);
                path2.push_back(tilePosition + Vector2f(8, 8));
            }
            else if (tileChar == '4' or tileChar == '5') {
                shared_ptr<Floor> newFloor = make_shared<Floor>(tilePosition);
                tileMap.push_back(newFloor);
                shared_ptr<Door> newTile = make_shared<Door>(tilePosition);
                if (tileChar == '5') {
                    newTile->getSprite()->setTexture(doorTileRightTexture);
                }
                tileMap.push_back(newTile);
            }
            tilePosition.x += 16;
        }
        tilePosition.y += 16;
        tilePosition.x = 450;
    }
    
    shared_ptr<PatrollingEnemy> patrolEnemy1 = make_shared<PatrollingEnemy>(path1);
    enemyList.push_back(patrolEnemy1);
    shared_ptr<PatrollingEnemy> patrolEnemy2 = make_shared<PatrollingEnemy>(path2);
    enemyList.push_back(patrolEnemy2);
    
    Event event;
    Clock mainClock;


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

    Text victory;
    victory.setFont(mainFont);
    string victoryMessage = "        VICTORY\nyou succesfully escaped!\n-press escape to close-";
    victory.setString(victoryMessage);
    victory.setFillColor(Color(255, 255, 20));
    victory.setCharacterSize(15);
    victory.setOrigin(Vector2f(90, 20));
    victory.setPosition(mainView.getCenter());

    Text playerKeyNumber;
    playerKeyNumber.setFont(mainFont);
    playerKeyNumber.setCharacterSize(15);

    while (isGameRunning) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed and Keyboard::isKeyPressed(Keyboard::Escape)) {
                cout << "close\n";
                /*isPauseMenu = true;*/
                isGameRunning = false;
            }
            else if (event.type == Event::Closed) { isGameRunning = false; }
        }
        if (player.getHp() <= 0 or chrono <= 0) {
            gameOver.setPosition(mainView.getCenter());
            window.clear();

            window.draw(gameOver);

            window.display();
        }
        else if (player.getSprite()->getPosition().y < 0.5f) {
            victory.setPosition(mainView.getCenter());
            window.clear();

            window.draw(victory);

            window.display();
        }
        else {
            chrono -= gameTime.restart().asSeconds();
            if (chrono <= 15) {
                chronoText.setFillColor(Color(255, 30, 30));
            }
            mainView.setCenter(player.getSprite()->getPosition());
            window.setView(mainView);
            chronoText.setPosition(mainView.getCenter() - mainView.getSize()/10.f*4.f);
            string chronoString = to_string(chrono);
            for (int i = 0; i < chronoString.size(); i++) {
                char c = chronoString[i];
                if (c == '.') {
                    while (i + 2 < chronoString.size() - 1) {
                        chronoString.erase(i + 3);
                    }
                    break;
                }
            }
            chronoText.setString(chronoString + "s");

            timeSinceLastFrame = mainClock.restart();
            game.update();
            playerKeyNumber.setPosition(playerKey->getPosition() + Vector2f(playerKey->getLocalBounds().getSize().x, playerKey->getLocalBounds().getSize().y) / 2.f);
            playerKeyNumber.setString("x" + to_string(player.getKeyState()));

            window.clear();

            for (shared_ptr<Tile> tile : tileMap) {
                if (tile) {
                    window.draw(*tile->getSprite());
                }
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
            for (shared_ptr<Key> key : keyList) {
                if (key) {
                    key->draw();
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
            if (player.getKeyState() > 0) {
                window.draw(*playerKey);
                window.draw(playerKeyNumber);
            }
            window.draw(chronoText);

            window.display();
        }
    }
    window.close(); exit(1);
}

