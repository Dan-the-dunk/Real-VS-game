#include"Game.h"
#include"SDL_Ultis.h"
#include<iostream>
using namespace std;
Game::Game() {

}

Game::~Game() {

}


void Game::init(const char* title, SDL_Window* gWindow, SDL_Renderer* gRenderer, int width, int height, bool fullscreen) {
	initSDL("FUCKERY", gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT,  fullscreen);
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
	SDL_RenderCopy(gRenderer, playerTex, NULL, NULL);
	SDL_RenderPresent(gRenderer);
};

void Game::clean() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyTexture(playerTex);
	SDL_Quit();
	cout << "SDL has been cleaned";
};





