
#include"assets/TextureManager.h"
#include "SDL.h"
#include "Game.h"
#include "Gamestate.h"
#include "menuState.h"

CMenuState CMenuState::m_MenuState;

const int x_pos = 351;

void CMenuState::Init()
{
	bg = loadTexture("assets/image/menu.png");
	fader = loadTexture("assets/image/fader.png");


	

	Button con_butt = Button("assets/image/button/con_button.png", x_pos, 200, 150);
	buttons.push_back(con_butt);

	Button play_butt = Button("assets/image/button/play_button.png", x_pos, 320, 150);
	buttons.push_back(play_butt);

	Button exit_butt = Button("assets/image/button/exit_button.png", x_pos, 440, 150);
	buttons.push_back(exit_butt);

	setBlendMode(SDL_BLENDMODE_BLEND, &fader);
	setBlendMode(SDL_BLENDMODE_BLEND, &bg);
	// fill the fader surface with black


	//SDL_RenderFillRect(Game::gRenderer, &introRect);

	// start off opaque
	alpha = 255;

	setAlpha(alpha, &fader);



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


	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Game::isRunning = false;
			break;


			

		case SDL_MOUSEBUTTONDOWN:
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i].getStatus())
				{
					switch (i)
					{

					case 0:
						game->PopState();
						Mix_PlayMusic(CPlayState::bgm, -1);
						break;
					case 1:

						game->CleanAllAndCreate(CPlayState::Instance());
						break;

					case 2:
						game->isRunning = false;
						break;
					}
				}
			}


		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				game->PopState();
				Mix_PlayMusic(CPlayState::bgm, -1);
				break;
			}
			break;
		}
	}
}

void CMenuState::Update(Game* game)
{
	alpha--;


	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].CheckInside(&event);
	}

	if (alpha < 63) alpha = 63;
	setAlpha(63, &fader);
}

void CMenuState::Draw(Game* game)
{
	
	//SDL_RenderCopy(Game::gRenderer, bg, NULL, NULL);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].Render();
	}

	SDL_RenderPresent(Game::gRenderer);
}
