#include"Hero.h"


Hero::Hero(const char* texturelink, SDL_Renderer* renderer, int x, int y) {
	hRenderer = renderer;
	hTexture = loadTexture(texturelink, hRenderer);
	xpos = x;
	ypos = y;
}

Hero::~Hero()
{
}


void Hero::update() {
	xpos++;
	ypos++;
	scrRect = { 0,0,140,140 };
	desRect = { xpos,ypos, scrRect.w , scrRect.h };



}


void Hero::render() {
	SDL_RenderCopy(hRenderer, hTexture, &scrRect, &desRect);
}

