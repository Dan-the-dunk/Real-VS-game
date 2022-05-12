#pragma once


#include "Game.h"
#include"Gamestate.h"
class CIntroState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Game* game);
	void Update(Game* game);
	void Draw(Game* game);

	static CIntroState* Instance() {
		return &m_IntroState;
	}

protected:
	CIntroState() { }

private:
	static CIntroState m_IntroState;

	SDL_Texture* bg;
	SDL_Texture* fader;
	int alpha;
};
