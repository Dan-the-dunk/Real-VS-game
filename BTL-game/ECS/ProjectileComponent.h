#pragma once


#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"
#include"../Gamestate.h"
#include"../playState.h"



class ProjectileComponent : public Component
{
public:

	const int projectile_speed = 2;

	ProjectileComponent(int rng , int sp, Vector2D vel , string id) : range(rng) , speed(sp) , velocity(vel) , pId(id)
	{}

	ProjectileComponent(int rng, int sp, Vector2D vel ) : range(rng), speed(sp), velocity(vel)
	{}

	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();


	}
	
	void update() override
	{
		distance += speed;
		
		p_way.set_vlength(pPos, transform->position, projectile_speed);
			

		transform->position += velocity;

		if (distance > range)
		{

			
			
			if (pId == "e_projectile1")
			{
				cout << "3 small missle"<<endl ;
				CPlayState::assets->CreateProjectile(transform->position, 200, 2, "e_projectile1_m", p_way );
				//CPlayState::assets->CreateProjectile(transform->position, 200, 2, "e_projectile1_m", Vector2D(p_way.x , ( p_way.y + 0.5f)) );
				//CPlayState::assets->CreateProjectile(transform->position, 200, 2, "e_projectile1_m", Vector2D(p_way.x, ( p_way.y - 0.5f))  );
			}

			cout << " out of range" << endl;
			entity->destroy();
			
		}

	}


	void getPlayerMove(Vector2D p_pos)
	{
		pPos = p_pos;
		
	}


private:
	TransformComponent* transform;

	
	string pId = "";
	int speed = 0;
	int range = 0;
	int distance = 0;

	Vector2D pPos;
	Vector2D p_way;
	Vector2D velocity;

};