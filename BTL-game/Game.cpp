#include"Game.h"
#include"SDL_Ultis.h"
#include<iostream>
#include"Hero.h"
#include"Map.h"
#include"ECS.h"
#include"Components.h"


using namespace std;



Hero* hero1 = nullptr;
Hero* hero2 = nullptr;
SDL_Renderer* Game::gRenderer = nullptr;
Map* maplv1 = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());



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

				
				

				//load media o day;
				

			}
		}
	}
	



};


void Game::loadMap() {
	maplv1 = new Map();
	
}


void Game::loadMedia() {
	backgroundTxt = loadTexture(backgroundImagePath);
	gameOverTxt = loadTexture(gameOverImagePath);
	hero1 = new Hero("image/arnold.png" , 0, 0);
	hero2 = new Hero("image/enemy.png", 200, 200);
	
	//load ecs

	newPlayer.addComponent<PositionComponent>();
	
}

void Game::handleEvents() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT) {
			isRunning = false;
		}
		else {

		}
	}
};


void Game::update() {
	hero1->update();
	hero2->update();
	manager.update();
	cout << newPlayer.getComponent<PositionComponent>().getXpos() << " , "
		<< newPlayer.getComponent<PositionComponent>().getYpos() << endl;

};

void Game::render() {
	SDL_RenderClear(gRenderer);
	//add things to render 
	maplv1->drawmap();
	hero1->render();
	hero2->render();
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





