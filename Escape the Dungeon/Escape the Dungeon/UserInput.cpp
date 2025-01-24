#include "UserInput.hpp"



void userInput() {
    Clock mainClock;
    vector<shared_ptr<Tile>> toDeleteTiles = {};
    while (isGameRunning) {
        timeSinceLastFrameInputs = mainClock.restart();
        for (int i = 0; i < tileMap.size(); i++) {
            shared_ptr<Tile> tile = tileMap[i];
            if (tile->getSprite()) {
                if (tile->getSprite()->getGlobalBounds().intersects(player.getHitBox())) {
                    if (tile->getType() == "Door" and player.getKeyState() > 0) {

                        if (find(toDeleteTiles.begin(), toDeleteTiles.end(), tileMap[i]) == toDeleteTiles.end()) {
                            player.setKeyState(player.getKeyState() - 1);
                            toDeleteTiles.push_back(tile);
                        }
                        if (i > 1) {
                            if (tileMap[i - 2]->getType() == "Door" and find(toDeleteTiles.begin(), toDeleteTiles.end(), tileMap[i - 2]) == toDeleteTiles.end()) {
                                toDeleteTiles.push_back(tileMap[i - 2]);
                            }
                        }
                        if (i + 2 < tileMap.size() - 1) {
                            if (tileMap[i + 2]->getType() == "Door" and find(toDeleteTiles.begin(), toDeleteTiles.end(), tileMap[i + 2]) == toDeleteTiles.end()) {
                                toDeleteTiles.push_back(tileMap[i + 2]);
                            }
                        }
                        continue;
                    }
                    if (tile->getType() == "Wall" or tile->getType() == "Door") {
                        inputMovement *= -2.f;
                        player.move();
                        break;
                    }
                }
            }
        }
        for (shared_ptr<Tile> tile : toDeleteTiles) {
            auto pos = find(tileMap.begin(), tileMap.end(), tile);
            tileMap.erase(pos);
        }
        toDeleteTiles.clear();

        inputMovement = Vector2f(0, 0.f);
        if (Keyboard::isKeyPressed(Keyboard::Scancode::A)) {
            inputMovement += Vector2f(-1.f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Scancode::W)) {
            inputMovement += Vector2f(0, -1.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Scancode::S)) {
            inputMovement += Vector2f(0, 1.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Scancode::D)) {
            inputMovement += Vector2f(1, 0.f);
        }
        if ((inputMovement.x < 0 and player.getSprite()->getScale().x > 0) or (inputMovement.x > 0 and player.getSprite()->getScale().x < 0)) {
            player.getSprite()->setScale(player.getSprite()->getScale().x * (-1.f), player.getSprite()->getScale().y);
        }
        player.move();
    }
}
