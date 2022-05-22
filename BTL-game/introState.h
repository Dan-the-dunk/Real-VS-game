#pragma once


#include "Game.h"
#include"Gamestate.h"
#include"Button.h"


#define BUTTON_HEIGHT 98
#define BUTTON_WIDTH 150



class CIntroState : public CGameState
{
public:


	static bool inIntro;
	static SDL_Event event;

	Button back_butt;

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(Game* game);
	void Update(Game* game);
	void Draw(Game* game);

	static CIntroState* Instance(bool status) {
		inIntro = status;
		return &m_IntroState;
	}

protected:
	CIntroState() { }

private:


	bool isOnHelp = false;
	

	static CIntroState m_IntroState;

	/*
	SDL_Rect play_rect, help_rect, exit_rect;

	SDL_Rect cPlay_rect, cHelp_rect, cExit_rect;


	SDL_Texture* play_tex;
	SDL_Texture* help_tex;
	SDL_Texture* exit_tex;*/

	
	vector<Button> buttons ;


	SDL_Texture* intro_bg;
	SDL_Texture* currentBg;
	SDL_Texture* help_bg;
	SDL_Texture* bg;
	SDL_Texture* fader;
	int alpha;
};
