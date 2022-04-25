#pragma once
#include<SDL.h>
#include"assets//AssetsManager.h"
#include"Game.h"
#include<string>


const int tile_size = 32;

class Map
{
public:
	Map();
	~Map();

	static void loadmap(std::string path , int sizeX, int sizeY);


// stop at 11:33

private:

};
