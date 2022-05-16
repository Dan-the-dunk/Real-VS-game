#ifndef SDL_ULTIS_H
#define SDL_ULTIS_H



#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include<iostream>
#include "../Game.h"
#include"../Physics/Vector2D.h"
#include"../playState.h"



const int FRAME_NUMBER = 4;

SDL_Texture* loadTexture(const char* path);

void setBlendMode(SDL_BlendMode blending, SDL_Texture** mTexture);


void setAlpha(Uint8 alpha, SDL_Texture** mTexture);


void drawTexture(SDL_Texture* texture, SDL_Rect scr, SDL_Rect des, SDL_RendererFlip flip );


void bounce_back(Vector2D& vel , bool bounce_right);

void updateCam(int xpos, int ypos , int mapXmax , int mapYmax );




#endif 