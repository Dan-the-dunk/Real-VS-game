#pragma once
#include<SDL.h>
#include"assets//AssetsManager.h"
#include"Game.h"
#include<string>


const int tile_size = 32;

class Map
{
public:
	Map(const char* mfp, int ms , int ts);
	~Map();

	void loadmap(std::string path , int sizeX, int sizeY);
	void AddTitle(int srcX, int srcY, int xpos, int ypos);

// stop at 11:33

private:
	const char* mapFilepath;
	int mapScale;
	int tileSize;
	int scaledSize;
};
