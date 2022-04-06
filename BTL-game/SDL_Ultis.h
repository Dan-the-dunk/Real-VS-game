#ifndef SDL_ULTIS_H
#define SDL_ULTIS_H



#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include<iostream>
using namespace std;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAME_NUMBER = 4;

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer) {};

bool initSDL(const char* title, SDL_Window* gWindow, SDL_Renderer* gRenderer, int width, int height, bool fullscreen) {

	
		int flag = 0;


		if (fullscreen) {
			flag = SDL_WINDOW_FULLSCREEN;
		}
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			cout << "Failed to init SDL " << SDL_GetError() << endl;
			isRunning = false;
		}
		else {
			gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
			if (gWindow == NULL) {
				cout << "Failed to create window " << SDL_GetError() << endl;
				isRunning = false;

			}
			else {
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL) {
					cout << "Failed to create renderer " << SDL_GetError() << endl;
					isRunning = false;

				}
				else {

					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError();
						isRunning = false;
					}
					isRunning = true;

					backgroundTxt = loadTexture(backgroundImagePath, gRenderer);

					//gameOverTxt = loadTexture(gameOverImagePath, gRenderer);

				}
			}
		}
	};


}

#endif 