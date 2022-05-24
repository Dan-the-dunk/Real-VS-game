#pragma once


#include "SDL.h"
#include "GameState.h"
#include<vector>
#include<SDL_image.h>
#include<string>
#include<sdl_mixer.h>




class Level
{
public:

	
	string map_lnk;
	string ssheet_link;

};





class CPlayState : public CGameState
{
public:

	static int current_lv ;

	static Mix_Music* bgm;
	static bool gameOver;

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



	
	static Mix_Chunk* jump;
	static Mix_Chunk* get_hit;
	static Mix_Chunk* die;
	static Mix_Chunk* fart;
	static Mix_Chunk* strong_fart;




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
	
	

	vector<Level*> g_levels;


	
	//more detail

	SDL_Texture* fader;
	int alpha;
};




