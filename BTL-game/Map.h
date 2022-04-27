#pragma once
#include<SDL.h>
#include"assets//AssetsManager.h"
#include"Game.h"
#include<string>


const int tile_size = 32;
const int xMax = 1000;
const int yMax = 30;


class Map
{
public:
	

	int cMap[xMax][yMax];
	Map(const char* mfp, int ms , int ts , int sizeX , int sizeY);
	~Map();

	void loadmap(std::string path );
	

	void drawMap();

	

// stop at 11:33

private:

	//co the can xMax = (sizeX + 1) * tileSize;

	SDL_Texture* texture;
	
	int startX, startY;
	int mapXmax;
	const char* mapFilepath;
	int sizeX;
	int sizeY;
	int mapScale;
	int tileSize;
	int scaledSize;
};
