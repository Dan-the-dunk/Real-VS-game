#ifndef HERO_H
#define HERO_H

#include"Game.h"
#include<SDL.h>
#include"assets/TextureManager.h"


class Hero
{
public:
	Hero(const char* texturelink, int xpos, int ypos);

	~Hero();


	void update();
	void render();

private:
	int xpos, ypos;
	SDL_Texture* hTexture;

	SDL_Rect scrRect, desRect;


};



#endif // !HERO_H




