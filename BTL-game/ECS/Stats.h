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
		currentCharge = 0;
		fart_lv = 60;
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
			cout << "Charging"<<" ";
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

		}

		desRect.x = transform->position.x - Game::camera.x ;
		desRect.y = transform->position.y - bar_height * 2 - Game::camera.y ;
		// dong nay de bi lech du lieu
		//srcRect.w = (currentCharge / fartMax) * 32;
		srcRect.w = (currentCharge / fartMax) * 32;
		//cout << srcRect.w << endl;

		
	}

	void draw() override
	{
		cout << srcRect.h << endl;
		if (charging)
		{
			drawTexture(pTexture, srcRect, desRect, SDL_FLIP_NONE);
		}
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Texture* pTexture;
	SDL_Rect desRect, srcRect;
	const int fart_charge_speed = 1;
	float fartMax = 120.0f ;
	float fart_lv;
	float currentCharge ;
	bool isUp = true;
};
