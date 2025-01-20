#include "UserInput.hpp"



void userInput() {
    while (isGameRunning) {
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
