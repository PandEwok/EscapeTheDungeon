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
        player.move();
    }
}
