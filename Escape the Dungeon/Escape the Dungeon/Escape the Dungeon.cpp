// Escape the Dungeon.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Global.hpp"
#include "UserInput.hpp"
#include "Entity.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;



int main() {
    loadTextures();
    thread uInputThread(userInput);
    uInputThread.detach();
    Event event;
    Clock mainClock;
    Game game;
    while (isGameRunning) {
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
        player.draw();

        window.display();
    }
    window.close(); exit(1);
}

