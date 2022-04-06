#ifndef SDL_ULTIS_H
#define SDL_ULTIS_H



#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include<iostream>
#include "Game.h"
using namespace std;


const int FRAME_NUMBER = 4;



bool initSDL(const char* title, SDL_Window* gWindow, SDL_Renderer* gRenderer, int width, int height, bool fullscreen) ;




#endif 