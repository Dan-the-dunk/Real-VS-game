#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Game.h"
#include"RigidBody.h"





class KeyboardController : public Component{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	RigidBody* body;
	//test ri tao rigidbody

	

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();

		
		body = &entity->getComponent <RigidBody>();

		sprite = &entity->getComponent <SpriteComponent>();



		
	}

	void update() override 
	{
		if (Game::ev.type == SDL_KEYDOWN) 
		{	
			

			switch (Game::ev.key.keysym.sym)
			{
			case SDLK_UP:
			case SDLK_SPACE:
	
				body->onground = false;
				cout << "UP" << endl;
				//140 = char_size
				
				
				transform->velocity.y = -2;				
				break;
			case SDLK_DOWN:

				transform->velocity.y = 1;
				break;

			case SDLK_LEFT:
				cout << "LEFT" << endl;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;

				transform->velocity.x = -1;
				break;

			case SDLK_RIGHT:
				cout << "RIGHT" << endl;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;

				transform->velocity.x = 1;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;

			default:
				break;
			}

			

		}

		if (Game::ev.type == SDL_KEYUP) 
		{
			switch (Game::ev.key.keysym.sym)
			{

			
			
			case SDLK_UP:
			
				transform->velocity.y = 0;
				break;
			

			case SDLK_DOWN:
			
				transform->velocity.y = 0;
				break;
			
			

			case SDLK_LEFT:
				
				sprite->play("Idle");
				transform->velocity.x = 0;
				//sprite->spriteFlip = SDL_FLIP_NONE;
				break;

			case SDLK_RIGHT:
				sprite->play("Idle");
				transform->velocity.x = 0;
				break;

			default:
				break;
			}
		}

		

	}
};