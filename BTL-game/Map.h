#pragma once
#include<SDL.h>
#include"SDL_Ultis.h"
#include"Game.h"
class Map
{
public:
	Map();
	~Map();

	void loadmap(int arr[32][18]);
	void drawmap();
	SDL_Rect srcRect, desRect;

	SDL_Texture* grassTxt;
	SDL_Texture* dirtTxt;
	SDL_Texture* waterTxt;

	
	int map[32][18];

private:

};
