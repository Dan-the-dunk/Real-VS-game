#include"Map.h"
#include"Game.h"
#include<fstream>

			  


Map::Map()
{

}

Map::~Map()
{

}






void Map::loadmap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);


	int srcX, srcY;


	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tile_size;
			mapFile.get(c);
			srcX = atoi(&c) * tile_size;



			Game::AddTitle(srcX,srcY, x* tile_size, y* tile_size);
			mapFile.ignore();
		}
	}



	mapFile.close();

}