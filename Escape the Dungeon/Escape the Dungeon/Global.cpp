#include "Global.hpp"

using namespace sf;
using namespace std;

string whiteString = "\033[0m";
string greenString = "\033[32m";
string redString = "\033[31m";

float screenWidth = 1200.f, screenHeight = screenWidth/4*3;
RenderWindow window(VideoMode(screenWidth, screenHeight), "Escape The Dungeon", Style::Close);
View mainView(FloatRect(screenWidth / 2, screenHeight / 2, 220, 220/4*3));
bool isGameRunning = true;
Time timeSinceLastFrame;

Texture playerTexture;
Texture hpBarTexture;
Vector2f inputMovement = Vector2f(0.f, 0.f);
int playerScore = 0;

Font mainFont;
Texture backgroundTexture;

Texture coinTexture;
vector<shared_ptr<Sprite>> coinList;

Texture chaserEnemyTexture;

void loadTextures() {
    mainFont.loadFromFile("Fonts/Perfect DOS VGA 437 Win.ttf");
    mainFont.setSmooth(false);
	playerTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/Character_animation/monsters_idle/vampire/v1/vampire_idle.png");
    hpBarTexture.loadFromFile("Images/CrimsonFantasyGUI/AnimationSheets/HealthRegeneration/hpBar.png");
	backgroundTexture.loadFromFile("Images/map_dungeon.png");
    coinTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/items and trap_animation/coin/coin_idle.png");
    chaserEnemyTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/Character_animation/monsters_idle/skull/v1/skull_idle.png");
}

void continueAnimation(shared_ptr<Sprite> sprite) {
    const Texture* texture = sprite->getTexture();
    if (sprite->getTextureRect().left >= texture->getSize().x - sprite->getTextureRect().width) {
        sprite->setTextureRect(IntRect(0, 0, sprite->getTextureRect().width, sprite->getTextureRect().height));
    }
    else {
        IntRect rect = sprite->getTextureRect();
        rect.left += sprite->getTextureRect().width;
        sprite->setTextureRect(rect);
    }
}

Vector2f normalize(Vector2f value)
{
    float baseX = 1.f;
    float baseY = 1.f;
    if (value.x < 0) {
        baseX = -1.f;
    }
    if (value.y < 0) {
        baseY = -1.f;
    }
    if (abs(value.x) > abs(value.y)) {
        return Vector2f(baseX, baseY - baseY * abs(value.y / value.x));
    }
    else if (abs(value.x) < abs(value.y)) {
        return Vector2f(baseX - baseX * abs(value.x / value.y), baseY);
    }
    else {
        return Vector2f(baseX, baseY);
    }
}

