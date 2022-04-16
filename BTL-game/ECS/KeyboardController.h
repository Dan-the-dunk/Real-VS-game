#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Game.h"


class KeyboardController : public Component{
public:
	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override 
	{
		if (Game::ev.type == SDL_KEYDOWN) 
		{
			switch (Game::ev.key.keysym.sym)
			{

			case SDLK_UP:
			case SDLK_SPACE:
				cout << "UP" << endl;
				transform->velocity.y = -7;
				break;

			case SDLK_DOWN:
				cout << "DOWN" << endl;
				transform->velocity.y = 1;
				break;

			case SDLK_LEFT:
				cout << "LEFT" << endl;
				transform->velocity.x = -1;
				break;

			case SDLK_RIGHT:
				cout << "RIGHT" << endl;
				transform->velocity.x = 1;
				break;

			default:
				break;
			}
		}

		if (Game::ev.type == SDL_KEYUP) 
		{
			switch (Game::ev.key.keysym.sym)
			{

			/*
			case SDLK_UP:
			
				transform->velocity.y = 0;
				break;

			case SDLK_DOWN:
			
				transform->velocity.y = 0;
				break;
				*/

			case SDLK_LEFT:
			
				transform->velocity.x = 0;
				break;

			case SDLK_RIGHT:
			
				transform->velocity.x = 0;
				break;

			default:
				break;
			}
		}

		

	}
};