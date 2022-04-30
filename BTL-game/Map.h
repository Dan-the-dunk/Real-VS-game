#pragma once
#include<SDL.h>
#include"assets//AssetsManager.h"
#include"Game.h"
#include<string>


const int tile_size = 32;

const int xMax = 1000;
const int yMax = 100;
const int lMax = 10;

const int blank_tile = -1;

class Map
{
public:
	

	const int BLANK_TILE = -1;

	int sizeX;
	int sizeY;
	int mapScale;
	int tileSize;
	int mapXmax, mapYmax;

	int cMap[yMax][xMax];
	Map(const char* mfp, int ms , int ts , int sizeX , int sizeY);
	~Map();

	void loadmap(std::string path );
	

	void drawMap(SDL_Rect cam);


// stop at 11:33

private:

	//co the can xMax = (sizeX + 1) * tileSize;




	SDL_Texture* texture;
	int startX, startY;
	const char* mapFilepath;
	int scaledSize;

};
