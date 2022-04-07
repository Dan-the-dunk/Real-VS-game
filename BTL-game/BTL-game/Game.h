#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<SDL.h>
#include"Hero.h"


const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


class Game
{
public:


	
	const char* backgroundImagePath = "image/gameover.jpg";
	const char* gameOverImagePath = "image/colors.png";
	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;



	Game();
	~Game();
	void init(const char* title , bool fullscreen );
	
	void handleEvents();
	void update();
	void render();
	void renderGameover();
	void clean();
	void loadMedia();
	

	
	bool running(){
		return isRunning;
	};

private:
	int cnt = 0;
	bool isRunning;
	SDL_Renderer* gRenderer;
	SDL_Window* gWindow;
	

	//Testing zone
	


};




#endif // !
