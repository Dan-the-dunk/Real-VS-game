#include"Hero.h"


Hero::Hero(const char* texturelink, int x, int y) {
	
	hTexture = loadTexture(texturelink);
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
	SDL_RenderCopy(Game::gRenderer, hTexture, &scrRect, &desRect);
}

