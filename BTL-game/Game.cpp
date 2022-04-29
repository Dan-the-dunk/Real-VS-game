#include"Game.h"
#include"assets/AssetsManager.h"
#include<iostream>
#include"Map.h"
#include"ECS/Components.h"
#include"Physics/Vector2D.h"
#include"Collision.h"


using namespace std;

Map* maplv1 = nullptr;
Manager manager;


bool Game::isRunning = false;
SDL_Rect Game::camera = { 0,0,SCREEN_WIDTH  , SCREEN_HEIGHT };

SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::ev ;

auto& newPlayer(manager.addEntity());



//testing extern
extern bool onground;


Game::Game() {
	
}

Game::~Game() {

}



void Game::init(const char* title, bool fullscreen) {
	
	int flag = 0;
	isRunning = true;

	if (fullscreen) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Failed to init SDL " << SDL_GetError() << endl;
		isRunning = false;

	}
	else 
	{
		gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flag);
		if (gWindow == NULL) {
			cout << "Failed to create window " << SDL_GetError() << endl;
			isRunning = false;

		}
		else 
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) 
			{
				cout << "Failed to create renderer " << SDL_GetError() << endl;
				isRunning = false;

			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError();
					isRunning = false;
				}

								

			}
		}
	}
	



};





void Game::loadMedia() {
	
	//loadbackground;
	backgroundTxt = loadTexture(backGroundImagePath);
	
	
	



	//load component(pos , sprite)

	maplv1 = new Map("assets/map_terrain.png", 1, 32 , 36 , 24);
	//qua ton ram, nen de background thi hon/.

	maplv1 -> loadmap("assets/map_col.map");
	

	//thu picture perfect
	newPlayer.addComponent<TransformComponent>(32,32);
	newPlayer.addComponent<SpriteComponent>("assets/image/dirt_txt.png",false);
	newPlayer.addComponent<RigidBody>(1);
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);







}



auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents() {
	
	SDL_PollEvent(&ev);

	switch (ev.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
};


void checkCollsionMap(Map* map) 
{
	bool check_onground = false;

	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	newPlayer.getComponent<RigidBody>().onground = false;

	Vector2D pos = newPlayer.getComponent<TransformComponent>().position;
	Vector2D vel = newPlayer.getComponent<TransformComponent>().velocity;
	
	int cWidth = newPlayer.getComponent<TransformComponent>().width;
	int cHeight = newPlayer.getComponent<TransformComponent>().height;


	// check vertical


	int min_width = cWidth > map->tileSize ? map->tileSize : cWidth;

	x1 = (pos.x) / map->tileSize;
	x2 = (pos.x + min_width) / map->tileSize;

	y1 = (pos.y + vel.y) / map->tileSize;
	y2 = (pos.y + vel.y + cHeight - 1) / map->tileSize;

	if (x1 >= 0 && x2 <= map->sizeX && y1 >= 0 && y2 <= map->sizeY)
	{
		if (vel.y > 0)
		{
			if (map->cMap[y2][x1] != map->BLANK_TILE || map->cMap[y2][x2] != map->BLANK_TILE)
			{
				pos.y = y2 * map->tileSize;
				pos.y -= cHeight ;
				vel.y = 0;
				newPlayer.getComponent<RigidBody>().onground = true;
			}
		}

		else if (vel.y < 0)
		{
			if (map->cMap[y1][x1] != map->BLANK_TILE || map->cMap[y1][x2] != map->BLANK_TILE)
			{
				pos.y = (y1 + 1) * map->tileSize;
				vel.y = 0;
			}
		}



	}








	x1 = (pos.x + vel.x) / map->tileSize;
	x2 = (pos.x + vel.x + cWidth  - 1 ) / map->tileSize;

	int min_height = cHeight > map->tileSize ? map->tileSize : cHeight;

	y1 = (pos.y ) / map->tileSize;
	y2 = (pos.y + min_height - 1) / map->tileSize;



	if (x1 >= 0 && x2 <= map->sizeX && y1 >= 0 && y2 <= map->sizeY)
	{
		if (vel.x > 0)
		{
			//check move right
			if (map->cMap[y1][x2] != map->BLANK_TILE || map->cMap[y2][x2] != map->BLANK_TILE)
			{
				pos.x = x2 * map->tileSize;
				pos.x -= cWidth + 1;
				vel.x = 0;

			}
		}
		else if (vel.x < 0)
		{
			//check move right
			if (map->cMap[y1][x1] != map->BLANK_TILE || map->cMap[y2][x1] != map->BLANK_TILE)
			{
				pos.x = (x1 + 1) * map->tileSize;
				vel.x = 0;

			}
		}
	}
	

	if (pos.x < 0) pos.x = 0;
	else if (pos.x + cWidth >= map->sizeX * map->tileSize) pos.x = map->sizeX * map->tileSize - cWidth - 1;




	//test operator overload
	
	newPlayer.getComponent<TransformComponent>().position = pos;

	newPlayer.getComponent<TransformComponent>().velocity = vel;



}


void Game::update() 
{
	
	//sprite component

	// xem truoc khi update y nam o dau

	

	manager.refresh();
	manager.update();
	
	checkCollsionMap(maplv1);


	




	camera.x = newPlayer.getComponent<TransformComponent>().position.x - SCREEN_WIDTH/2; // gioi han vi tri nhan vat.
	camera.y = newPlayer.getComponent<TransformComponent>().position.y - SCREEN_HEIGHT;


	//Camera
	if (camera.x < 0) camera.x = 0;// 0 tac dong gi
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y < 0) camera.y = 0;// 0 tac dong gi
	if (camera.y > camera.h) camera.y = camera.h;

	
	



	cout << newPlayer.getComponent<TransformComponent>().position.x << " , "
		<< newPlayer.getComponent<TransformComponent>().position.y << endl;


	
	
	/*mm leak
	if (newPlayer.getComponent<TransformComponent>().position.x >= 300) {
	
		newPlayer.getComponent<SpriteComponent>().setText("image/cbum.png");
	}*/
	
	

	


	
};





void Game::render() {
	SDL_RenderClear(gRenderer);
	
	maplv1->drawMap();


	
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& c : colliders)
	{
		c->draw();
	}

	SDL_RenderPresent(gRenderer);
};

void Game::renderGameover() {
	SDL_RenderClear(gRenderer);
	//add things to render 
	SDL_RenderCopy(gRenderer, gameOverTxt, NULL, NULL);
	SDL_RenderPresent(gRenderer);
};

void Game::clean() {
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyTexture(backgroundTxt);
	backgroundTxt = nullptr;
	SDL_DestroyTexture(gameOverTxt);
	gameOverTxt = nullptr;
	SDL_Quit();
	cout << "SDL has been cleaned";
};



	



