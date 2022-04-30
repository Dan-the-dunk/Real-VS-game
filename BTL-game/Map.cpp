#include"Map.h"
#include"Game.h"
#include<fstream>
#include"ECS/ECS.h"
#include"ECS/Components.h"
#include"assets/AssetsManager.h"

extern Manager manager;
			  



Map::Map(const char* mfp, int ms, int ts , int sX , int sY) : mapFilepath(mfp), mapScale(ms), tileSize(ts), sizeX(sX) , sizeY(sY)
{
	scaledSize = ms * ts;
	mapXmax = sX * ts;
	mapYmax = sY * ts;
	texture = loadTexture(mapFilepath);
}

Map::~Map()
{

}






void Map::loadmap(std::string path)
{

	char c;
	std::fstream mapFile;
	mapFile.open(path);


	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			cMap[y][x] = atoi(&c) * 10;

			

			mapFile.get(c);
			
			cMap[y][x] += atoi(&c);

			cMap[y][x] -= 1;
			cout << cMap[y][x] << " ";
			
			mapFile.ignore();
		}
		cout << endl;
	}

	startX = 0;
	startY = 0;


}




void Map::drawMap(SDL_Rect cam) {
	

	//drawbackground shiet;
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;





	//
	x1 = cam.x / tileSize ;
	x2 = x1 + SCREEN_WIDTH / tileSize + 1 > mapXmax ? mapXmax : x1 + SCREEN_WIDTH / tileSize + 1;

	y1 = cam.y / tileSize;
	y2 = y1 + (SCREEN_HEIGHT)/tileSize + 1 ;


	for (int y = y1; y <= y2; y++)
	{
		for (int x = x1; x <= x2; x++)
		{
			SDL_Rect srcRect, desRect;

			int yval = cMap[y][x] / 10;
			int xval = cMap[y][x] % 10;

			srcRect = { xval * tileSize , yval * tileSize , tileSize , tileSize };
			desRect = { x * tileSize - Game::camera.x , y * tileSize - Game::camera.y , scaledSize , scaledSize };
			
			
			drawTexture(texture, srcRect, desRect, SDL_FLIP_NONE);
		}
	}
		







}