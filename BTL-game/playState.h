#pragma once


#include "SDL.h"
#include "GameState.h"

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Game* game);
	void Update(Game* game);
	void Draw(Game* game);

	static CPlayState* Instance() {
		return &m_PlayState;
	}

protected:
	CPlayState() { }

private:
	static CPlayState m_PlayState;

	SDL_Texture* bg;
};

