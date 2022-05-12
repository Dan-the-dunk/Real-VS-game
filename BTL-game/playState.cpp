#include"playState.h"
#include<SDL.h>
#include"Game.h"
#include"Gamestate.h"
#include"menuState.h"
#include"assets/TextureManager.h"

void CPlayState::Init()
{
	bg = loadTexture("assets/image/menu.png");

	printf("CPlayState Init\n");


	//init a whole lotta shit . 
}

void CPlayState::Cleanup()
{
	SDL_DestroyTexture(bg);

	printf("CPlayState Cleanup\n");
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
}

void CPlayState::HandleEvents(Game* game)
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
				Game::isRunning = false;
				break;
			case SDLK_m:
				game->PushState(CMenuState::Instance());
				break;
			}
			break;
		}
	}
}

void CPlayState::Update(Game* game)
{


}

void CPlayState::Draw(Game* game)

{




	SDL_RenderCopy(Game::gRenderer, bg, NULL, NULL);
}

