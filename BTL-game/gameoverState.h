#pragma once


#include<SDL.h>
#include"Gamestate.h"
#include"Button.h"

class CGameoverState : public CGameState
{
public:

	
	static SDL_Event event;
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Game* game);
	void Update(Game* game);
	void Draw(Game* game);

	static CGameoverState* Instance() {
		return &m_GameoverState;
	}

protected:
	CGameoverState() { }

private:
	static CGameoverState m_GameoverState;

	vector<Button> buttons;
	
	bool isOnCre = false;


	SDL_Texture* current_bg;
	SDL_Texture* credit_tex;
	SDL_Texture* bg;
};




