#pragma once

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
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

extern float screenWidth, screenHeight;
extern RenderWindow window;
extern bool isGameRunning;
extern Time timeSinceLastFrame;

extern Texture playerTexture;
extern Vector2f inputMovement;

extern Texture backgroundTexture;

void loadTextures();