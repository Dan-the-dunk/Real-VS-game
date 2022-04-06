#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<iostream>

#include<SDL.h>

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, SDL_Window* gWindow,SDL_Renderer* gRenderer, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	//testing zone
	string backgroundImagePath = "image/colors.png";
	string gameOverImagePath = "image/gameover.png";
	//
	bool running(){
		return isRunning;
	};

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	

	//Testing zone
	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;


};




#endif // !
