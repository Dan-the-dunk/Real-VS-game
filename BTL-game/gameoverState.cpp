
#include"assets/TextureManager.h"
#include "SDL.h"
#include "Game.h"
#include "Gamestate.h"
#include "gameoverState.h"

CGameoverState CGameoverState::m_GameoverState;

void CGameoverState::Init()
{
	bg = loadTexture("assets/image/menu.png");


	printf("CGameoverState Init\n");
}

void CGameoverState::Cleanup()
{
	SDL_DestroyTexture(bg);

	printf("CGameoverState Cleanup\n");
}

void CGameoverState::Pause()
{
	printf("CGameoverState Pause\n");
}

void CGameoverState::Resume()
{
	printf("CGameoverState Resume\n");
}

void CGameoverState::HandleEvents(Game* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Game::isRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				game->ChangeState(CPlayState::Instance());
				break;
			}
			break;
		}
	}
}

void CGameoverState::Update(Game* game)
{

}

void CGameoverState::Draw(Game* game)
{
	SDL_RenderCopy(Game::gRenderer, bg, NULL, NULL);

	SDL_RenderPresent(Game::gRenderer);
}
