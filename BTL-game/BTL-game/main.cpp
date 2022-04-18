#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"Game.h"
#include"SDL_Ultis.h"
#include"Hero.h"
using namespace std;



Game* newgame = nullptr;


const int FPS = 60;
const int frameDelay = 1000 / FPS;
int frameTime;

Uint32 frameStart;


//initialize window,texture etc..
int main(int argc, char* argv[]) {

	

	newgame->init("ah finally", false);
	newgame->loadMedia();

	
	while (newgame->running()) {

		frameStart = SDL_GetTicks();
		newgame->handleEvents();
		
		
		newgame->update();

		newgame->render();




		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		
	}
	newgame->renderGameover();

	SDL_Delay(2000);
	newgame->clean();
	delete newgame;
	return 0;
}