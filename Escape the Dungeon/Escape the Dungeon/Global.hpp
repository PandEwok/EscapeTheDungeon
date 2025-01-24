#pragma once

#include <iostream>
#include <fstream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <chrono>

using namespace std;
using namespace sf;

extern string whiteString;
extern string greenString;
extern string redString;

extern float screenWidth, screenHeight;
extern RenderWindow window;
extern View mainView;
extern bool isGameRunning;
extern Time timeSinceLastFrame;
extern Time timeSinceLastFrameInputs;

extern Texture playerTexture;
extern Texture hpBarTexture;
extern shared_ptr<Sprite> hpBar;
extern Vector2f inputMovement;
extern int playerScore;
extern Texture playerKeyTexture;
extern shared_ptr<Sprite> playerKey;

extern Font mainFont;
extern Texture backgroundTexture;

extern Texture coinTexture;
extern Texture potionHealTexture;
extern Texture keyTexture;

extern Texture chaserEnemyTexture;
extern Texture patrollingEnemyTexture;

extern Texture wallTileTexture;
extern Texture wallTileSideTexture;
extern Texture wallTileBackTexture;
extern Texture wallTileBackEndTexture;
extern Texture wallTileBackIntersectionTexture;
extern Texture wallTileMiddleTexture;
extern Texture wallTileMiddleEndTexture;
extern Texture wallTileIntersectionTexture;
extern Texture wallTileIntersectionSideTexture;
extern Texture floorTileTexture;
extern Texture doorTileLeftTexture;
extern Texture doorTileRightTexture;
extern Texture flagTileTexture;
extern Texture candleTexture;

void loadTextures();

void continueAnimation(shared_ptr<Sprite> sprite);

Vector2f normalize(Vector2f value);