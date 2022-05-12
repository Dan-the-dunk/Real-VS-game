#include"introState.h"
#include<SDL.h>
#include"Gamestate.h"
#include"introState.h"
#include"playState.h"
#include<iostream>
#include"assets/TextureManager.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{

	bg = loadTexture("assets/image/intro.png");
	fader = loadTexture("assets/image/fader.png");

	SDL_Rect introRect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };


	// create the fader surface like the background with alpha
	
	setBlendMode(SDL_BLENDMODE_BLEND, &fader);
	// fill the fader surface with black
	

	//SDL_RenderFillRect(Game::gRenderer, &introRect);

	// start off opaque
	alpha = 255;

	setAlpha(alpha, &fader);

	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(fader);

	printf("CIntroState Cleanup\n");
}

void CIntroState::Pause()
{
	printf("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	printf("CIntroState Resume\n");
}

void CIntroState::HandleEvents(Game* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Game::isRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				game->ChangeState(CPlayState::Instance());
				break;

			case SDLK_ESCAPE:
				game->isRunning = false;
				break;
			}
			break;
		}
	}
}

void CIntroState::Update(Game* game)
{
	alpha--;

	if (alpha < 0)
		alpha = 0;

	setAlpha(alpha , &fader);
}

void CIntroState::Draw(Game* game)
{
	//SDL_BlitSurface(bg, NULL, game->screen, NULL);

	SDL_RenderCopy(Game::gRenderer, bg, NULL, NULL);

	// no need to blit if it's transparent
	if (alpha != 0)
		//SDL_BlitSurface(fader, NULL, game->screen, NULL);
		SDL_RenderCopy(Game::gRenderer, fader, NULL, NULL);

	
}
