#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Game.h"
#include"RigidBody.h"
#include"Stats.h"
#include<SDL_mixer.h>


class KeyboardController : public Component{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	RigidBody* body;
	Stats* stats;
	bool turnLeft = false;
	//test ri tao rigidbody

	

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();

		
		body = &entity->getComponent <RigidBody>();
		stats = &entity->getComponent <Stats>();
		sprite = &entity->getComponent <SpriteComponent>();



		
	}

	void update() override 
	{
		if (CPlayState::ev.type == SDL_KEYDOWN)
		{	
			

			switch (CPlayState::ev.key.keysym.sym)
			{
			

			
			case SDLK_UP:
			case SDLK_SPACE:
				
				if (body->onground == true)
				{


					Mix_PlayChannel(1, CPlayState::jump, 0);

					//140 = char_size
					transform->velocity.y = -12;
				}

				break;
			
			/*
			case SDLK_DOWN:

				transform->velocity.y = 2;
				break;*/
			
			case SDLK_LEFT:
				if (!body->bouncing_back)
				{
					turnLeft = true;
					sprite->play("Walk");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;

					transform->velocity.x = -2;
				}
				
				break;

			case SDLK_RIGHT:
				
				if (!body->bouncing_back)
				{
					turnLeft = false;
					sprite->play("Walk");
					sprite->spriteFlip = SDL_FLIP_NONE;

					transform->velocity.x = 2;
				}
				break;

			case SDLK_f:
				stats->charging = true;
				break;

			case SDLK_ESCAPE:
				Game::isRunning = false;


			default:
				break;
			}

			

		}

		if (CPlayState::ev.type == SDL_KEYUP)
		{
			switch (CPlayState::ev.key.keysym.sym)
			{

			
			
			/*
			case SDLK_DOWN:
			case SDLK_UP:
				sprite->play("Idle");
				transform->velocity.y = 0;
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			
			*/

			case SDLK_LEFT:
			case SDLK_RIGHT:
				sprite->play("Idle");
				transform->velocity.x = 0;
					//sprite->spriteFlip = SDL_FLIP_NONE;
				
				break;

			case SDLK_f:
				//if(turnLeft) transform->velocity.x = -(stats->getFartPercent() * 12) / 100;
				//else transform->velocity.x = (stats->getFartPercent() * 12) / 100;
				transform->velocity.y = -2*(stats->getFartPercent() * 12) / 100;
				stats->MinusFart();
				Mix_PlayChannel(1, CPlayState::fart, 0);
				stats->charging = false;

			default:
				break;
			}
		}

		

	}
};