#include"Game.h"
#include"assets/AssetsManager.h"
#include<iostream>
#include"Map.h"
#include"ECS/Components.h"
#include"Physics/Vector2D.h"
#include"Collision.h"


using namespace std;

const char* mapFile = "assets/terrain_ss.png";

vector<ColliderComponent*>Game::colliders;


SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::ev ;
Map* maplv1 = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());
auto& wall(manager.addEntity());



enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupProjectitles
};



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
	maplv1 = new Map();
	//load component(pos , sprite)




	Map::loadmap("assets/map.map", 36, 24);





	newPlayer.addComponent<TransformComponent>(72,119);
	newPlayer.addComponent<SpriteComponent>("assets/image/f_petersprite.png",true);
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<RigidBody>(0.2f);
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);







}

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


void Game::update() {
	
	//sprite component
	
	manager.refresh();
	manager.update();
	


	for (auto cc : colliders)
	{
		Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
	
	}
	



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


auto& titles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


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
	for (auto& e : enemies)
	{
		e->draw();
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

void Game::AddTitle(int srcX, int srcY , int xpos , int ypos ) 
{
	auto& title(manager.addEntity());
	title.addComponent<TitleComponenet>(srcX, srcY, xpos, ypos,mapFile);
	title.addGroup(groupMap);
}



