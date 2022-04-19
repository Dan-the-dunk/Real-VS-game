#ifndef SDL_ULTIS_H
#define SDL_ULTIS_H



#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include<iostream>
#include "../Game.h"
using namespace std;


const int FRAME_NUMBER = 4;

SDL_Texture* loadTexture(const char* path);

void drawTexture(SDL_Texture* texture, SDL_Rect scr, SDL_Rect des);






#endif 