#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<SDL.h>


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


class Game
{
public:


	
	const char* backgroundImagePath = "image/colors.png";
	const char* gameOverImagePath = "image/gameover.jpg";
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
	
	static SDL_Renderer* gRenderer;
	static SDL_Event ev;

	bool running(){
		return isRunning;
	};

private:
	int cnt = 0;
	
	bool isRunning ;
	
	SDL_Window* gWindow;
	

	//Testing zone
	


};




#endif // !
