#include "Global.hpp"

using namespace sf;
using namespace std;

float screenWidth = 1200.f, screenHeight = screenWidth/4*3;
RenderWindow window(VideoMode(screenWidth, screenHeight), "Escape The Dungeon", Style::Close);
bool isGameRunning = true;
Time timeSinceLastFrame;

Texture playerTexture;
Vector2f inputMovement = Vector2f(0.f, 0.f);

Texture backgroundTexture;

void loadTextures() {
	playerTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/Character_animation/monsters_idle/vampire/v1/vampire_v1_1.png");
	backgroundTexture.loadFromFile("Images/background_dungeon.png");
}