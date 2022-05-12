
#include"assets/TextureManager.h"
#include "SDL.h"
#include "Game.h"
#include "Gamestate.h"
#include "menuState.h"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init()
{
	bg = loadTexture("assets/image/menu.png");


	printf("CMenuState Init\n");
}

void CMenuState::Cleanup()
{
	SDL_DestroyTexture(bg);

	printf("CMenuState Cleanup\n");
}

void CMenuState::Pause()
{
	printf("CMenuState Pause\n");
}

void CMenuState::Resume()
{
	printf("CMenuState Resume\n");
}

void CMenuState::HandleEvents(Game* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Game::isRunning = false();
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				game->PopState();
				break;
			}
			break;
		}
	}
}

void CMenuState::Update(Game* game)
{

}

void CMenuState::Draw(Game* game)
{
	SDL_RenderCopy(Game::gRenderer, bg, NULL, NULL);
}
