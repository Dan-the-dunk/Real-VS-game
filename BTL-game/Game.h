#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<SDL_image.h>
#include<vector>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;



class ColliderComponent;

class CGameState;


class AssetsManager;

class Game
{
public:
	
	static bool isRunning;
	static SDL_Renderer* gRenderer;
	
	
	// them cai nay.
	

	//play sate
	//static SDL_Rect camera;
	//static AssetsManager* assets;

	/*
	const char* gameOverImagePath = "assets/image/gameover.jpg";
	const char* backGroundImagePath = "assets/image/3.png";
	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;*/

	/*
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectitles
	};
*/

	




	Game();
	~Game();
	void init(const char* title , bool fullscreen );
	
	void handleEvents();
	void update();
	void render();


	// cho vao playstate
	//void renderGameover();
	void clean();
	void loadMedia();
	


	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();


	

	bool running(){
		return isRunning;
	};

private:

	vector<CGameState*> states;
	
	
	SDL_Window* gWindow;
	

	//Testing zone
	


};




#endif // !
