#pragma once


#include "SDL.h"
#include "GameState.h"
#include<vector>
#include<SDL_image.h>
#include<string>

const int max_lv = 10;


class Level
{
public:

	
	string map_lnk;
	string ssheet_link;

};





class CPlayState : public CGameState
{
public:
	void Init(); // = load media.
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Game* game);
	void Update(Game* game);
	void Draw(Game* game);

	static CPlayState* Instance() {
		return &m_PlayState;
	}


	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectitles,
		groupLabels
	};



	//tu game.h
	void renderGameover();
	void clean();



	static SDL_Event ev;
	static SDL_Rect camera;
	static AssetsManager* assets;

	//static bool game_over;


	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;
	const char* gameOverImagePath = "assets/image/gameover.jpg";
	const char* backGroundImagePath = "assets/image/3.png";


protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;
	SDL_Texture* bg;
	int current_lv = 1;
	

	vector<Level*> g_levels;


	//more detail

	SDL_Texture* fader;
	int alpha;
};




