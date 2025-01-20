#pragma once

#include <iostream>
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

extern Texture playerTexture;
extern Texture hpBarTexture;
extern Vector2f inputMovement;
extern int playerScore;

extern Font mainFont;
extern Texture backgroundTexture;

extern Texture coinTexture;
extern vector<shared_ptr<Sprite>> coinList;

extern Texture chaserEnemyTexture;

void loadTextures();

void continueAnimation(shared_ptr<Sprite> sprite);

Vector2f normalize(Vector2f value);