#pragma once
#include"Components.h"
#include<SDL.h>
#include"../assets/TextureManager.h"
#include"Animation.h"
#include"../Game.h"
#include"../Gamestate.h"
#include"../playState.h"


const int hp_max = 4;

class Stats : public Component
{
public:
	const int bar_width = 32, bar_height = 12;

	const int hp_width = 150, hp_height = 31;
	int hp;
	float fart_lv;
	bool charging = false;

	SDL_Rect fart_box;
	bool farting_f;



	~Stats()
	{
		SDL_DestroyTexture(hTexture);
		SDL_DestroyTexture(hbTexture);
		SDL_DestroyTexture(p0Texture);
		SDL_DestroyTexture(pTexture);
	}

	void init() override 
	{
		

		hp = 4;

		pTexture = loadTexture("assets/image/pbar_slider.png");
		p0Texture = loadTexture("assets/image/pbar_base.png");
		hTexture = loadTexture("assets/image/health.png");
		hbTexture = loadTexture("assets/image/health_bar.png");

		if (pTexture == NULL) cout << "cant load hbar";

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

		srcRect = { 0 , 0 , 0 , bar_height };
		bSrcRect = { 0 , 0 , bar_width , bar_height };


		hSrc = { 0 , 0 , hp_width  , hp_height };
		hpDes = { 20 , 20 , hp_width , hp_height };

		hDes = hpDes;


		desRect = { (int)transform->position.x , (int)transform->position.y - bar_height * 2 , bar_width , bar_height };

		bDesRect = { (int)transform->position.x , (int)transform->position.y - bar_height * 2 , bar_width , bar_height };
	}

	void update() override
	{
	
		farting_f = false;




		

		if (hp > hp_max) hp = hp_max;

		//if (hp <= 0) CPlayState::game_over = true;

		if (fart_lv > fartMax)
		{
			
			transform->velocity.y = -20;
			Mix_PlayChannel(1, CPlayState::strong_fart, 0);
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


		
		hSrc.w =  24 + (hp * 31);
		hDes.w = hSrc.w;

		cout << hSrc.w << endl;

		// dong nay de bi lech du lieu
		
		fart_box = { (int)transform->position.x + 32, (int)transform->position.y , 32 ,32 };
		
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

		
		drawTexture(hTexture, hSrc, hDes, SDL_FLIP_NONE);
		SDL_RenderCopy(Game::gRenderer, hbTexture, NULL, &hpDes);
	

		SDL_SetRenderDrawColor(Game::gRenderer, 0, 0, 255, 255);
		SDL_RenderDrawLine(Game::gRenderer, desRect.x + (fart_lv / fartMax) * 32, desRect.y, desRect.x + (fart_lv / fartMax) * 32, desRect.y + 12);
	}

private:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Texture* pTexture;
	SDL_Texture* p0Texture;

	SDL_Rect hpDes;
	SDL_Rect hSrc;
	SDL_Rect hDes;

	SDL_Texture* hTexture;
	SDL_Texture* hbTexture;

	SDL_Rect desRect, srcRect;
	SDL_Rect bDesRect, bSrcRect;
	
	const int fart_charge_speed = 2;
	float currentCharge;
	const float fartMax = 120.0f ;
	
	
	bool isUp = true;
	Uint8 a = 255;
};
