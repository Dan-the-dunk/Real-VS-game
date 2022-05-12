#pragma once
#include"Components.h"
#include<SDL.h>
#include"../assets/TextureManager.h"
#include"Animation.h"
#include"../Game.h"
#include"../Gamestate.h"
#include"../playState.h"
class Stats : public Component
{
public:
	const int bar_width = 32, bar_height = 12;
	int hp;
	float fart_lv;
	bool charging = false;

	
	void init() override 
	{
		pTexture = loadTexture("assets/image/pbar_slider.png");
		p0Texture = loadTexture("assets/image/pbar_base.png");

		setBlendMode(SDL_BLENDMODE_BLEND, &pTexture);
		setBlendMode(SDL_BLENDMODE_BLEND, &p0Texture);

		currentCharge = 0;
		fart_lv = 80;
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();
		sprite = &entity->getComponent <SpriteComponent>();

		srcRect = { 0 , 0 , 0 , 12 };
		bSrcRect = { 0 , 0 , bar_width , bar_height };

		desRect = { transform->position.x , transform->position.y - bar_height * 2 , bar_width , bar_height };

		bDesRect = { transform->position.x , transform->position.y - bar_height * 2 , bar_width , bar_height };
	}

	void update() override
	{
		
		if (fart_lv > fartMax)
		{
		
			transform->velocity.y = -20;
			fart_lv = fartMax/2;
		}
		if (charging)
		{
			//set alphablending;
			a = 255;

			if (isUp)
			{
				
				currentCharge += fart_charge_speed;
				if (currentCharge > fart_lv)
				{
					isUp = false;
				
				}
			}

			if (!isUp)
			{
				
				currentCharge -= fart_charge_speed;
				if (currentCharge < 0)
				{
					isUp = true;

				}
			}
			srcRect.w = (currentCharge / fartMax) * 32;
			desRect.w = (currentCharge / fartMax) * 32;


		}

		if (!charging) 
		{
			a = 100;
			currentCharge = 0;
			srcRect.w = (fart_lv / fartMax) * 32;
			desRect.w = (fart_lv / fartMax) * 32;

		}

		desRect.x = transform->position.x - CPlayState::camera.x ;
		bDesRect.x = desRect.x;

		desRect.y = transform->position.y - bar_height * 2 - CPlayState::camera.y ;
		bDesRect.y = desRect.y;
		// dong nay de bi lech du lieu
		
		
		//cout << srcRect.w << endl;

		
	}


	int getFartPercent()
	{
		return (currentCharge / fartMax) * 100;
	}

	void MinusFart()
	{
		fart_lv -= currentCharge;
	}

	void draw() override
	{
		
		setAlpha(a, &pTexture);
		setAlpha(a, &p0Texture);

		drawTexture(p0Texture,bSrcRect , bDesRect, SDL_FLIP_NONE);
		drawTexture(pTexture, srcRect, desRect, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(Game::gRenderer, 0, 0, 255, 255);
		SDL_RenderDrawLine(Game::gRenderer, desRect.x + (fart_lv / fartMax) * 32, desRect.y, desRect.x + (fart_lv / fartMax) * 32, desRect.y + 12);
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Texture* pTexture;
	SDL_Texture* p0Texture;

	SDL_Rect desRect, srcRect;
	SDL_Rect bDesRect, bSrcRect;
	
	const int fart_charge_speed = 2;
	float currentCharge;
	const float fartMax = 120.0f ;
	
	
	bool isUp = true;
	Uint8 a = 255;
};
