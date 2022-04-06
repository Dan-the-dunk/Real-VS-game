#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"Game.h"
using namespace std;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


Game* newgame = nullptr;

//initialize window,texture etc..
int main(int argc, char* argv[]) {

	newgame = new Game();
	newgame->init("DAMN BRO TACH FILE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,false);
	while (newgame->running()) {

		newgame->handleEvents();
		newgame->update();
		newgame->render();

		
	}

	newgame->clean();
	return 0;
}
