#pragma warning(disable : 4996)
#include"Map.h"
#include"Game.h"
#include<fstream>
#include"ECS/ECS.h"
#include"ECS/Components.h"
#include"assets/AssetsManager.h"
#include<format>
extern Manager manager;
			  



Map::Map(const char* mfp, int ms, int ts , int sX , int sY , int nol) : mapFilepath(mfp), mapScale(ms), tileSize(ts), sizeX(sX) , sizeY(sY) , num_of_layers(nol)
{
	scaledSize = ms * ts;
	mapXmax = sX * ts;
	mapYmax = sY * ts;
	texture = loadTexture(mapFilepath);
	
	string str;
	for (int i = 0; i < nol; i++)
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




void Map::drawMap(int velx) {
	

	//drawbackground shiet;




	//SDL_Rect bgSrcRect ;
	//SDL_Rect bgResRect ;
	// scrolling n shiet. da xong pseudo parallax, bay h chi can them vao keyboardinpu.
	for (int i = 0; i < num_of_layers; i++)
	{
		

		SDL_Rect bgDesRect1 , bgDesRect2 ;
		scrollingOffset[i] = (float)i / 2 * Game::camera.x;
		scrollingOffset[i] =  -(scrollingOffset[i] % SCREEN_WIDTH ); //i*velocity.x;
		


		/*
		if (scrollingOffset[i] < -SCREEN_WIDTH)
		{
			scrollingOffset[i] = 0;
		}*/

		/*
		if (scrollingOffset[i] > 0)
		{
			scrollingOffset[i] = 0;
		}*/
		

		//them 1 gioi han cho background.

		bgDesRect1 = { scrollingOffset[i] , 0  , SCREEN_WIDTH , SCREEN_HEIGHT};
		bgDesRect2 = { scrollingOffset[i] + SCREEN_WIDTH , 0  , SCREEN_WIDTH , SCREEN_HEIGHT};


		SDL_RenderCopy(Game::gRenderer, bgTex[i], NULL, &bgDesRect1);

		SDL_RenderCopy(Game::gRenderer, bgTex[i], NULL, &bgDesRect2);
	}
	

	//
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;





	//
	x1 = Game::camera.x / tileSize ;
	x2 = x1 + SCREEN_WIDTH / tileSize + 1 > mapXmax ? mapXmax : x1 + SCREEN_WIDTH / tileSize + 1;

	y1 = Game::camera.y / tileSize;
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