#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<SDL.h>
#include<vector>



const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


class ColliderComponent;





class Game
{
public:

	static bool isRunning;
	static SDL_Rect camera;

	
	const char* gameOverImagePath = "assets/image/gameover.jpg";
	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;
	static std::vector<ColliderComponent*> colliders;
	static void AddTitle(int srcX , int srcY , int xpos , int ypos);





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
	
	
	
	SDL_Window* gWindow;
	

	//Testing zone
	


};




#endif // !
