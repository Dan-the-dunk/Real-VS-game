#pragma once


#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"

class Enemy : public Component
{

public:

	//int height = 32;
	//int width = 32;
	int hp = 4;
	Vector2D velocity;

	Enemy(int rng, int sp, Vector2D vel, Vector2D pos ) : range(rng), speed(sp), velocity(vel), OgPos(pos) 
	{
	}

	~Enemy()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		
		sprite = &entity->getComponent<SpriteComponent>();


		sprite->play("Walk");
	}

	void update() override
	{
		/*
		
		if (e_timer.getTicks() >= 5000)
		{
			e_timer.start();
			//throw projectile.
		}
		*/

		distance += transform->velocity.x;

		// ham cho quay dau.
		


		transform->position += velocity;

		if (abs(transform->position.x - OgPos.x) >= range)
		{
			
			if(velocity.x > 0) sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			else sprite->spriteFlip = SDL_FLIP_NONE;

			//transform->velocity.x = - velocity.x;
			velocity.x = - velocity.x;
		}

		smtsmt();

	}


	virtual	void smtsmt(){};



private:


	//Timer e_timer;
	SpriteComponent* sprite;
	TransformComponent* transform;
	int speed = 0;
	int range = 0;
	int distance = 0;
	Vector2D OgPos;
	
};
