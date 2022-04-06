#include"Game.h"
#include"SDL_Ultis.h"
#include<iostream>

using namespace std;
SDL_Rect scrRect;
SDL_Rect desRect;


Game::Game() {

}

Game::~Game() {

}


void Game::init() {
	isRunning = initSDL("FUCKERY", gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	backgroundTxt = loadTexture("colors.png",gRenderer);
};

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
	cnt++;
	cout << cnt<<endl;
	
};

void Game::render() {
	SDL_RenderClear(gRenderer);
	//add things to render 
	SDL_RenderCopy(gRenderer, backgroundTxt, NULL, NULL);
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
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyTexture(backgroundTxt);
	SDL_DestroyTexture(gameOverTxt);
	SDL_Quit();
	cout << "SDL has been cleaned";
};





