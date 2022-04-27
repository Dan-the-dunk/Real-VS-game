#include"Map.h"
#include"Game.h"
#include<fstream>
#include"ECS/ECS.h"
#include"ECS/Components.h"

extern Manager manager;
			  



Map::Map(const char* mfp, int ms, int ts , int sX , int sY) : mapFilepath(mfp), mapScale(ms), tileSize(ts), sizeX(sX) , sizeY(sY)
{
	scaledSize = ms * ts;

}

Map::~Map()
{

}






void Map::loadmap(std::string path)
{
	
	char c;
	std::fstream mapFile;
	mapFile.open(path);


	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			cMap[y][x] = atoi(&c) * 10;
		
			//srcY = atoi(&c) * tileSize;

			mapFile.get(c);
			//srcX = atoi(&c) * tileSize;
			cMap[y][x] += atoi(&c);
			cout << cMap[y][x]<<" ";
			//AddTitle(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
		cout << endl;
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();

}

void Map::AddTitle(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TitleComponenet>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilepath);
	tile.addGroup(Game::groupMap);
}