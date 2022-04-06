#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<iostream>

#include<SDL.h>



const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


class Game
{
public:


	SDL_Renderer* gRenderer = NULL;
	SDL_Window* gWindow = NULL;
	const char* backgroundImagePath = "image/gameover.jpg";
	const char* gameOverImagePath = "image/colors.png";
	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;



	Game();
	~Game();
	void init();
	void handleEvents();
	void update();
	void render();
	void renderGameover();
	void clean();

	
	bool running(){
		return isRunning;
	};

private:
	int cnt = 0;
	bool isRunning;
	
	
	

	//Testing zone
	


};




#endif // !
