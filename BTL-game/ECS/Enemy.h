#pragma once


#include"ECS.h"
#include"Components.h"
#include<map>
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
	GTimer eTimer;
	const int projectile_speed = 3;




	Enemy(int rng, int sp, Vector2D vel, Vector2D pos, string id) : range(rng), speed(sp), velocity(vel), OgPos(pos), eID(id)
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


		

		p_way.set_vlength(pPos, transform->position , projectile_speed );
			
		//cout << p_way << endl ;


		if (OgPos.get_distance(transform->position, pPos) <= 200)
		{
			
			if (!eTimer.isStarted())
			{
				eTimer.start();

				sprite->play("Idle");

				//string pj_id = format("e_projectile{}", id);

				if (eID == "enemy1")
				{
					CPlayState::assets->CreateProjectile(transform->position, 200, 2, "e_projectile1", p_way);
					cout << "Start timer" << endl;
				}
				else
				{
					CPlayState::assets->CreateProjectile(transform->position, 200, 2, "projectile", p_way);
					cout << "Start timer" << endl;
				}
			}
			

			if (eTimer.getTicks() >= 4000)
			{
				eTimer.start();
				sprite->play("Idle");
				CPlayState::assets->CreateProjectile(transform->position, 200, 2, "projectile", p_way);
				cout << "Restart timer " << endl;

			}

			else 
			{

				if (eTimer.getTicks() < 500)
				{

				}

				else if (eTimer.getTicks() >= 500)

				{
					sprite->play("Walk");

					// chase enemy to range.
					if(hp >0 ) patrol();
				}

			}

			

		}

		else
		{
			
			if(hp > 0 )	patrol();
			
		}

		

		

	}

	void getPlayerMove(Vector2D p_pos , Vector2D p_vel)
	{
		pPos = p_pos;
		pVel = p_vel;
	}


	void patrol()
	{

		distance += transform->velocity.x;


		transform->position += velocity;

		if (abs(transform->position.x - OgPos.x) >= range)
		{


			if (velocity.x > 0) sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
			else sprite->spriteFlip = SDL_FLIP_NONE;

			//transform->velocity.x = - velocity.x;
			velocity.x = -velocity.x;
		}

		smtsmt();



	};


	virtual	void smtsmt(){};



private:


	
	SpriteComponent* sprite;
	
	string eID = "";
	int speed = 0;
	int range = 0;
	int distance = 0;
	bool is_throwing = false;


	Vector2D OgPos;
	Vector2D pPos, pVel;
	Vector2D p_way;
	TransformComponent* transform;
	
	
};
