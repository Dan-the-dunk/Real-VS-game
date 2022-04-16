#include"Game.h"
#include"SDL_Ultis.h"
#include<iostream>
#include"Map.h"
#include"ECS/Components.h"
#include"Physics/Vector2D.h"


using namespace std;



SDL_Renderer* Game::gRenderer = nullptr;
SDL_Event Game::ev ;
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





void Game::loadMedia() {
	backgroundTxt = loadTexture(backgroundImagePath);
	gameOverTxt = loadTexture(gameOverImagePath);
	maplv1 = new Map();
	//load component(pos , sprite)

	newPlayer.addComponent<TransformComponent>();
	newPlayer.addComponent<SpriteComponent>("image/arnold.png");
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<RigidBody>(0.2f);
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
	

	cout << newPlayer.getComponent<TransformComponent>().position.x << " , "
		<< newPlayer.getComponent<TransformComponent>().position.y << endl;


	/*
	Memory leak.

	if (newPlayer.getComponent<TransformComponent>().position.x >= 300) {
		newPlayer.getComponent<SpriteComponent>().setText("image/cbum.png");
	}

	*/


	if (newPlayer.getComponent<TransformComponent>().position.x >= SCREEN_WIDTH) {
		renderGameover();
		SDL_Delay(2000);
		isRunning = false;
	}
	 
};

void Game::render() {
	SDL_RenderClear(gRenderer);
	//add things to render 
	maplv1->drawmap();
	//
	//sprite component
	manager.draw();
	
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





