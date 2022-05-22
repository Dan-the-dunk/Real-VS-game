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


bool CIntroState::inIntro ;

void CIntroState::Init()
{

	bg = loadTexture("assets/image/menu_bg.jpg");
	help_bg = loadTexture("assets/image/help_bg.png");
	intro_bg = loadTexture("assets/image/intro_bg.png");

	currentBg = intro_bg;

	fader = loadTexture("assets/image/fader.png");
	
	Button play_butt =  Button("assets/image/button/play_button.png" , x_pos , 200 , 150);
	buttons.push_back(play_butt);
	Button help_butt =  Button("assets/image/button/help_button.png" , x_pos, 320 , 150);
	buttons.push_back(help_butt);
	Button exit_butt =  Button("assets/image/button/exit_button.png" , x_pos, 440 ,150);
	buttons.push_back(exit_butt);
	Button back_butt =  Button("assets/image/button/back_button.png" , 20 ,SCREEN_HEIGHT - 300 , 100 );
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


	if (inIntro)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Game::isRunning = false;
				break;
			case SDL_KEYDOWN:
				inIntro = false;
				currentBg = bg;
				break;
			}
		}
	
	}

	else 
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
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

							if (!isOnHelp)
							{
								isOnHelp = true;
							}
							else
							{
								isOnHelp = false;
								currentBg = bg;
							}

							break;

						}

					}
				}

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{

				case SDLK_ESCAPE:
					game->isRunning = false;
					break;


					break;
				}
			}
		}

	}


}

void CIntroState::Update(Game* game)
{

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].CheckInside(&event);

	}
	

	alpha -= 2;

	if (alpha < 0)
		alpha = 0;

	setAlpha(alpha , &fader);
}

void CIntroState::Draw(Game* game)
{
	//SDL_BlitSurface(bg, NULL, game->screen, NULL);

	SDL_RenderCopy(Game::gRenderer, currentBg, NULL, NULL);


	//
	if (!inIntro)
	{
		if (isOnHelp)
		{

			currentBg = help_bg;
			buttons[3].Render();
		}

		else
		{
			currentBg = bg;
			for (int i = 0; i < buttons.size() - 1; i++)
			{
				buttons[i].Render();

			}

		}
		
	}

	

	// no need to blit if it's transparent
	if (alpha != 0)
		//SDL_BlitSurface(fader, NULL, game->screen, NULL);
		SDL_RenderCopy(Game::gRenderer, fader, NULL, NULL);

	SDL_RenderPresent(Game::gRenderer);
	
}
