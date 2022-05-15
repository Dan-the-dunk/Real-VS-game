#pragma once


#include<SDL.h>
#include"Gamestate.h"

class CGameoverState : public CGameState
{
public:
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

	SDL_Texture* bg;
};




