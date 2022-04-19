#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<SDL.h>
#include<vector>



const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


class ColliderComponent;





class Game
{
public:


	
	const char* backgroundImagePath = "assets/image/colors.png";
	const char* gameOverImagePath = "assets/image/gameover.jpg";
	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;
	static std::vector<ColliderComponent*> colliders;
	static void AddTitle(int id, int x, int y);





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
