#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include<iostream>
#include "Game.h"
using namespace std;

class TexManager
{
public:
	static SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);

};

#endif // !
