#include"Game.h"
#include"assets/TextureManager.h"
#include<iostream>
#include"Map.h"
#include"ECS/Components.h"
#include"Physics/Vector2D.h"
#include"Collision.h"
#include<cmath>
#include"assets/AssetsManager.h"
#include<format>
#include"Gamestate.h"

using namespace std;


bool Game::isRunning = false;


SDL_Renderer* Game::gRenderer = nullptr;




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

				else
				{
					if (TTF_Init() == -1)
					{
					cout << "Failed to initialize ttf " << SDL_GetError() << endl;
					isRunning = false;
					}
						

				}
								

			}
		}
	}
	



};




void Game::ChangeState(CGameState* state)
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}


void Game::PushState(CGameState* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void Game::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}


void Game::handleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void Game::update()
{
	// let the state update the game
	states.back()->Update(this);
}

void Game::render()
{
	// let the state draw the screen
	states.back()->Draw(this);
}






void Game::clean() {

	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}


	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_Quit();
	cout << "SDL has been cleaned";
};



	



