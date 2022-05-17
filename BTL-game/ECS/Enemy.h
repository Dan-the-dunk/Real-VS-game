#pragma once


#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"
#include"../Timer.h"
#include"../assets/AssetsManager.h"
#include"../playState.h"
#include"../Gamestate.h"



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

		
		eTimer.start();


		transform = &entity->getComponent<TransformComponent>();
		
		sprite = &entity->getComponent<SpriteComponent>();


		sprite->play("Walk");



		
	}

	void update() override
	{


		
		
		
		

		p_way.set_vlength(pPos, transform->position , 2);
			
		cout << p_way << endl ;


		if (OgPos.get_distance(transform->position, pPos) <= 150)
		{

			//CPlayState::assets->CreateProjectile(transform->position, 120, 2, "projectile", p_way);

			eTimer.start();

			if (eTimer.getTicks() >= 5000)
			{
				eTimer.start();

			}

		}

		else
		{
			eTimer.stop();
		}

		

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

	void getPlayerMove(Vector2D p_pos , Vector2D p_vel)
	{
		pPos = p_pos;
		pVel = p_vel;
	}

	virtual	void smtsmt(){};



private:


	GTimer eTimer;
	SpriteComponent* sprite;
	
	int speed = 0;
	int range = 0;
	int distance = 0;


	Vector2D OgPos;
	Vector2D pPos, pVel;
	Vector2D p_way;
	TransformComponent* transform;
	
	
};
