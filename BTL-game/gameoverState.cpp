
#include"assets/TextureManager.h"
#include "SDL.h"
#include "Game.h"
#include "Gamestate.h"
#include "gameoverState.h"

CGameoverState CGameoverState::m_GameoverState;

const int x_pos = 351;

SDL_Event CGameoverState::event;

void CGameoverState::Init()
{
	bg = loadTexture("assets/image/go_bg.jpg");
	credit_tex = loadTexture("assets/image/cre_bg.png");
	current_bg = bg;

	Button replay_butt = Button("assets/image/button/play_button.png", x_pos, 200, 150);
	buttons.push_back(replay_butt);
	Button credit_butt = Button("assets/image/button/cre_button.png", x_pos, 440, 150);
	buttons.push_back(credit_butt);
	Button exit_butt = Button("assets/image/button/exit_button.png", x_pos, 320, 150);
	buttons.push_back(exit_butt);
	Button back_butt = Button("assets/image/button/back_button.png", 20, SCREEN_HEIGHT - 200, 100);
	buttons.push_back(back_butt);


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

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Game::isRunning = false;
			break;


		case SDL_MOUSEBUTTONDOWN:
			for (int i = 0; i < 4; i++)
			{
				if (buttons[i].getStatus())
				{
					switch (i)
					{

					case 0:
						if (!isOnCre)
						{
							game->ChangeState(CPlayState::Instance());
						}
						break;
					case 1:
						if (!isOnCre)
						{
							current_bg = credit_tex;
							isOnCre = true;
						}
						break;
					case 2:
						if (!isOnCre)
						{
							game->isRunning = false;
						}
						break;
					case 3:

						if (isOnCre)
						{
							isOnCre = false;
							current_bg = bg;
						}
						
						
						break;
					}

				}
			}

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
	for (int i = 0; i < 4; i++)
	{
		buttons[i].CheckInside(&event);

	}

}

void CGameoverState::Draw(Game* game)
{


	
	SDL_RenderCopy(Game::gRenderer, current_bg, NULL, NULL);

	if (isOnCre)
	{

		current_bg = credit_tex;
		buttons[3].Render();
	}

	else
	{
		current_bg = bg;
		for (int i = 0; i < 3; i++)
		{
			buttons[i].Render();

		}

	}

	
	SDL_RenderPresent(Game::gRenderer);
}
