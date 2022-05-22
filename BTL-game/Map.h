#pragma once
#include<SDL.h>
#include"assets/TextureManager.h"
#include"Game.h"
#include<string>
#include"Gamestate.h"
#include"playState.h"


const int tile_size = 32;
const int num_bg_layers = 3;
const int num_of_mlayers = 3;
const int xMax = 1000;
const int yMax = 100;
const int lMax = 10;


const int blank_tile = -1;


// format for bg name : "bg_l%s.png"





class gMap
{
public:

	gMap()
	{
		coss = 32;
	};
	int coss ;
	string tag;


	int cMap[yMax][xMax] = { 0 };

	void draw(SDL_Texture* tex, int velx, int mapXmax, int scaledSize);


	void load(string path, fstream* mapFile, int sizeX, int sizeY );

private:

	


};




class Map
{
public:
	
	const int WATER_TILE_s = 27;
	const int WATER_TILE_e = 29;

	const int BLANK_TILE = -1;
	const int death_lv = 960;
	const int FOOD_TILES = 5;
	const int SPIKE_TILES = 6;
	const int RICK = 59;

	gMap map[num_of_mlayers];
	SDL_Texture* texture;
	
	int sizeX = 0;
	int sizeY = 0;
	int mapScale = 0;
	int tileSize = 0;
	int mapXmax = 0, mapYmax = 0;
	int scaledSize = 0;
	
	
	Map(const char* mfp, int ms , int ts , int sizeX , int sizeY );
	~Map();

	void loadmap(std::string path);
	
		// dang co van de, phai load all 1 luc ms dc 

	
	

	void drawMap(int velx)
	{
		// tam thoi de o day, sau thu move sang file.cpp
		for (int i = 0; i < num_bg_layers; i++)
		{


			SDL_Rect bgDesRect1, bgDesRect2;
			scrollingOffset[i] = (float)i / 2 * CPlayState::camera.x;
			scrollingOffset[i] = -(scrollingOffset[i] % SCREEN_WIDTH); //i*velocity.x;





			bgDesRect1 = { scrollingOffset[i] , 0  , SCREEN_WIDTH , SCREEN_HEIGHT };
			bgDesRect2 = { scrollingOffset[i] + SCREEN_WIDTH , 0  , SCREEN_WIDTH , SCREEN_HEIGHT };


			SDL_RenderCopy(Game::gRenderer, bgTex[i], NULL, &bgDesRect1);

			SDL_RenderCopy(Game::gRenderer, bgTex[i], NULL, &bgDesRect2);
		}
		//

		for (int i = 0; i < num_of_mlayers - 1; i++)
			{
				map[i].draw(texture,velx, mapXmax , scaledSize);
			}
	}

	

// stop at 11:33

private:


	//co the can xMax = (sizeX + 1) * tileSize;
	
	

	int scrollingOffset[lMax] = {0};

	SDL_Texture* bgTex[5];
	
	int startX, startY;
	const char* mapFilepath;
	

};




