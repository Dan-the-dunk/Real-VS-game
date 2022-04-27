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
	gameOverTxt = loadTexture(gameOverImagePath);
	
	



	//load component(pos , sprite)

	maplv1 = new Map("assets/map_terrain.png", 1, 32 , 36 , 24);
	//qua ton ram, nen de background thi hon/.

	maplv1 -> loadmap("assets/map_col.map");
	

	//thu picture perfect
	newPlayer.addComponent<TransformComponent>(32,32);
	newPlayer.addComponent<SpriteComponent>("assets/image/dirt_txt.png",false);
	newPlayer.addComponent<RigidBody>(0.2f);
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);







}



auto& titles(manager.getGroup(Game::groupMap));
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


void Game::update() 
{
	
	//sprite component

	// xem truoc khi update y nam o dau

	manager.refresh();
	manager.update();

	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = newPlayer.getComponent<TransformComponent>().position;

	

	for (auto& c : colliders)
	{


		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))

		{
			cout << "HIT" << endl;
			newPlayer.getComponent<TransformComponent>().velocity.y = 0;
			newPlayer.getComponent<TransformComponent>().position.y = cCol.y - newPlayer.getComponent<RigidBody>().CHAR_SIZE - 1;
			newPlayer.getComponent<RigidBody>().onground = true;
			newPlayer.getComponent<RigidBody>().lockGround = true;
			break;
		}
		else {

			newPlayer.getComponent<RigidBody>().onground = false;
		}
		
	}





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
	
	

	


	if (newPlayer.getComponent<TransformComponent>().position.x >= SCREEN_WIDTH) {
		renderGameover();
		SDL_Delay(2000);
		isRunning = false;
	}
	 
};





void Game::render() {
	SDL_RenderClear(gRenderer);
	
	for (auto& t : titles)
	{
		t->draw();
	}
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



	



