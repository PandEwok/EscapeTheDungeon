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
Time timeSinceLastFrameInputs;

Texture playerTexture;
Texture hpBarTexture;
shared_ptr<Sprite> hpBar = make_shared<Sprite>();
Vector2f inputMovement = Vector2f(0.f, 0.f);
int playerScore = 0;
Texture playerKeyTexture;
shared_ptr<Sprite> playerKey = make_shared<Sprite>();

Font mainFont;
Texture backgroundTexture;

Texture coinTexture;
Texture potionHealTexture;
Texture keyTexture;

Texture chaserEnemyTexture;
Texture patrollingEnemyTexture;

Texture wallTileTexture;
Texture wallTileSideTexture;
Texture wallTileBackTexture;
Texture wallTileBackEndTexture;
Texture wallTileBackIntersectionTexture;
Texture wallTileMiddleTexture;
Texture wallTileMiddleEndTexture;
Texture wallTileIntersectionTexture;
Texture wallTileIntersectionSideTexture;
Texture floorTileTexture;
Texture doorTileLeftTexture;
Texture doorTileRightTexture;
Texture flagTileTexture;
Texture candleTexture;

void loadTextures() {
    mainFont.loadFromFile("Fonts/Perfect DOS VGA 437 Win.ttf");
    mainFont.setSmooth(false);
	playerTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/Character_animation/monsters_idle/vampire/v1/vampire_idle.png");
    hpBarTexture.loadFromFile("Images/CrimsonFantasyGUI/AnimationSheets/HealthRegeneration/hpBar.png");
    playerKeyTexture.loadFromFile("Images/Pixel Art Key Pack - Animated/Key 4/GOLD/Key 4 - GOLD - idle.png");
	backgroundTexture.loadFromFile("Images/map_dungeon.png");
    coinTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/items and trap_animation/coin/coin_idle.png");
    potionHealTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/items and trap_animation/flasks/flasks_1_idle.png");
    keyTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/items and trap_animation/keys/keys_1_idle.png");
    chaserEnemyTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/Character_animation/monsters_idle/skull/v1/skull_idle.png");
    patrollingEnemyTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/Character_animation/monsters_idle/skeleton1/v1/skeleton_idle.png");
    wallTileTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile.png");
    wallTileSideTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_side.png");
    wallTileBackTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_back.png");
    wallTileBackEndTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_back_end.png");
    wallTileBackIntersectionTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_back_intersection.png");
    wallTileMiddleTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_middle.png");
    wallTileMiddleEndTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_middle_end.png");
    wallTileIntersectionTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_intersection.png");
    wallTileIntersectionSideTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/wall_tile_intersection_side.png");
    floorTileTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/floor_tile.png");
    doorTileLeftTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/door_tile_left.png");
    doorTileRightTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/character and tileset/door_tile_right.png");
    flagTileTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/items and trap_animation/flag/flag_idle.png");
    candleTexture.loadFromFile("Images/2D Pixel Dungeon Asset Pack/items and trap_animation/torch/candlestick_2_idle.png");
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
    if (int(value.x) < 0) {
        baseX = -1.f;
    }
    else if (int(value.x) == 0) {
        baseX = 0;
    }
    if (int(value.y) < 0) {
        baseY = -1.f;
    }
    else if (int(value.y) == 0) {
        baseY = 0;
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

