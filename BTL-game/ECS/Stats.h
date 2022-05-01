#pragma once
#include"Components.h"
#include<SDL.h>
#include"../assets/AssetsManager.h"
#include"Animation.h"
#include"../Game.h"

class Stats : public Component
{
public:
	const int bar_width = 32, bar_height = 12;
	int hp;
	
	bool charging = false;

	
	void init() override 
	{
		pTexture = loadTexture("assets/image/f_powerbar.png");
		setBlendMode(SDL_BLENDMODE_BLEND, &pTexture);

		currentCharge = 0;
		fart_lv = 80;
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();
		sprite = &entity->getComponent <SpriteComponent>();

		srcRect = { 0 , 0 , 0 , 12 };
		desRect = { transform->position.x , transform->position.y - bar_height * 2 , bar_width , bar_height };
	}

	void update() override
	{
		
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

		desRect.x = transform->position.x - Game::camera.x ;
		desRect.y = transform->position.y - bar_height * 2 - Game::camera.y ;
		// dong nay de bi lech du lieu
		
		
		//cout << srcRect.w << endl;

		
	}


	int getFartPercent()
	{
		return (currentCharge / fartMax) * 100;
	}

	void draw() override
	{
		
		setAlpha(a, &pTexture);
		drawTexture(pTexture, srcRect, desRect, SDL_FLIP_NONE);
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Texture* pTexture;
	SDL_Texture* p0Texture;

	SDL_Rect desRect, srcRect;
	const int fart_charge_speed = 2;
	float fartMax = 120.0f ;
	float fart_lv;
	float currentCharge ;
	bool isUp = true;
	Uint8 a = 255;
};
