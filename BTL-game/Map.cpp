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
	char title;
	std::fstream mapFile;
	mapFile.open(path);


	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(title);
			Game::AddTitle(atoi(&title), x*30, y*30);
			mapFile.ignore();
		}
	}



	mapFile.close();

}