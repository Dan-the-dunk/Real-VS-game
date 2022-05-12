#pragma warning(disable : 4996)
#include"Map.h"
#include"Game.h"
#include<fstream>
#include"ECS/ECS.h"
#include"ECS/Components.h"
#include"assets/TextureManager.h"
#include"assets/AssetsManager.h"
#include<format>
extern Manager manager;
			  



Map::Map(const char* mfp, int ms, int ts , int sX , int sY ) : mapFilepath(mfp), mapScale(ms), tileSize(ts), sizeX(sX) , sizeY(sY) 
{
	scaledSize = ms * ts;
	mapXmax = sX * ts;
	mapYmax = sY * ts;
	
	
	texture = loadTexture(mapFilepath);
	
	
	string str;
	for (int i = 0; i < num_bg_layers; i++)
	{
		string str;
		str =  format("assets/tileset/bg_l{}.png", i);
		
		bgTex[i] = loadTexture(str.c_str());

	}

	//bgTex[1] = loadTexture("assets/tileset/bg_l0.png");

}

Map::~Map()
{

}






void Map::loadmap(std::string path)
{

	
	
	
	std::fstream mapFile;
	mapFile.open(path);

	for (int i = 0; i < num_of_mlayers; i++)
	{
		
		switch (i)
		{
		case 0:
			map[i].tag = "tile";
			break;
		case 1:
			map[i].tag = "item";
			break;
		case 2:
			map[i].tag = "enemy";
			break;

		default:
			break;
		}
		map[i].load(path , &mapFile , sizeX , sizeY);

	}
	cout << "load xong 3 layer";

}









void gMap::load(string path, fstream* mapFile, int sizeX, int sizeY)
{
	char c;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile->get(c);
			cMap[y][x] = atoi(&c) * 10;


			
			mapFile->get(c);

			cMap[y][x] += atoi(&c);

			cMap[y][x] -= 1;

			int tilecode = cMap[y][x];

			if (tag == "enemy" && tilecode != blank_tile)
			{
				string str = format("enemy{}", tilecode);
				
				
				CPlayState::assets->CreateEnemies(Vector2D(x  * tile_size, y * tile_size), 200, 2, str, Vector2D(1, 0));
			}
			//cout << cMap[y][x] << " ";

			mapFile->ignore();
		}
		//cout << endl;
	}

	mapFile->ignore();


}



void gMap::draw(SDL_Texture* tex, int velx , int mapXmax , int scaledSize)
{
	

	
	//
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;





	//
	x1 = CPlayState::camera.x / tile_size;
	x2 = x1 + SCREEN_WIDTH / tile_size + 1 > mapXmax ? mapXmax : x1 + SCREEN_WIDTH / tile_size + 1;

	y1 = CPlayState::camera.y / tile_size;
	y2 = y1 + (SCREEN_HEIGHT) / tile_size + 1;


	for (int y = y1; y <= y2; y++)
	{
		for (int x = x1; x <= x2; x++)
		{
			SDL_Rect srcRect, desRect;

			int yval = cMap[y][x] / 10;
			int xval = cMap[y][x] % 10;

			srcRect = { xval * tile_size , yval * tile_size , tile_size , tile_size };
			desRect = { x * tile_size - CPlayState::camera.x , y * tile_size - CPlayState::camera.y , scaledSize , scaledSize };


			drawTexture(tex, srcRect, desRect, SDL_FLIP_NONE);
		}
	}
}


