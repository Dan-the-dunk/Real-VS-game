#include"introState.h"
#include<SDL.h>
#include"Gamestate.h"
#include"introState.h"
#include"playState.h"
#include<iostream>
#include"assets/TextureManager.h"

CIntroState CIntroState::m_IntroState;

SDL_Event CIntroState::event;

const int  x_pos = 351;

void CIntroState::Init()
{

	bg = loadTexture("assets/image/intro.png");
	help_bg = loadTexture("assets/image/help_bg.png");
	currentBg = bg;

	fader = loadTexture("assets/image/fader.png");
	
	play_butt =  Button("assets/image/button/play_button.png" , x_pos , 200 , 150);
	buttons.push_back(play_butt);
	help_butt =  Button("assets/image/button/help_button.png" , x_pos, 320 , 150);
	buttons.push_back(help_butt);
	exit_butt =  Button("assets/image/button/exit_button.png" , x_pos, 440 ,150);
	buttons.push_back(exit_butt);
	back_butt =  Button("assets/image/button/back_button.png" , 20 ,SCREEN_HEIGHT - 300 , 100 );
	buttons.push_back(back_butt);




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


	/*
	delete(play_butt);
	delete(exit_butt);
	delete(help_butt);
	delete(back_butt);

	*/
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
						if (!isOnHelp)
						{
							game->ChangeState(CPlayState::Instance());
						}
						break;
					case 1:
						if (!isOnHelp)
						{
							isOnHelp = true;
						}
						break;
					case 2:
						if (!isOnHelp)
						{
							game->isRunning = false;
						}
						break;
					case 3:
						
						if (!isOnHelp) isOnHelp = true;
						else isOnHelp = false;
						
						
						break;

					}

				}
			}

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

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

	for (int i = 0; i < 4; i++)
	{
		buttons[i].CheckInside(&event);

	}
	back_butt.CheckInside(&event);

	alpha--;

	if (alpha < 0)
		alpha = 0;

	setAlpha(alpha , &fader);
}

void CIntroState::Draw(Game* game)
{
	//SDL_BlitSurface(bg, NULL, game->screen, NULL);

	SDL_RenderCopy(Game::gRenderer, currentBg, NULL, NULL);


	//
	

	if (isOnHelp)
	{

		currentBg = help_bg;
		back_butt.Render();
	}

	else
	{
		currentBg = bg;
		for (int i = 0; i < 3; i++)
		{
			buttons[i].Render();

		}

	}
	//

	// no need to blit if it's transparent
	if (alpha != 0)
		//SDL_BlitSurface(fader, NULL, game->screen, NULL);
		SDL_RenderCopy(Game::gRenderer, fader, NULL, NULL);

	SDL_RenderPresent(Game::gRenderer);
	
}
