#pragma once

#include<SDL.h>
#include"Gamestate.h"
#include"Button.h"
class CMenuState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Game* game);
	void Update(Game* game);
	void Draw(Game* game);

	static CMenuState* Instance() {
		return &m_MenuState;
	}

protected:
	CMenuState() { }


private:

	int alpha ;
	SDL_Event event;
	SDL_Texture* fader;
	static CMenuState m_MenuState;

	vector<Button> buttons;

	SDL_Texture* bg;
};




