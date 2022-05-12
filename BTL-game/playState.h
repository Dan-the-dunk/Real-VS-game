#pragma once


#include "SDL.h"
#include "GameState.h"
#include<vector>
#include<SDL_image.h>

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
		groupProjectitles
	};



	//tu game.h
	void renderGameover();
	void clean();
	void loadMedia();


	static SDL_Event ev;
	static SDL_Rect camera;
	static AssetsManager* assets;
	


	SDL_Texture* backgroundTxt;
	SDL_Texture* gameOverTxt;
	const char* gameOverImagePath = "assets/image/gameover.jpg";
	const char* backGroundImagePath = "assets/image/3.png";


protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	SDL_Texture* bg;
};

