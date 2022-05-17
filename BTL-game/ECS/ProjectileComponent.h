#pragma once


#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"
#include"../Gamestate.h"
#include"../playState.h"



class ProjectileComponent : public Component
{
public:

	ProjectileComponent(int rng , int sp, Vector2D vel ) : range(rng) , speed(sp) , velocity(vel)
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
		
		
			

		transform->position += velocity;

		if (distance > range)
		{
			cout << " out of range" << endl;
			entity->destroy();
		}

	

	}
private:
	TransformComponent* transform;

	int speed = 0;
	int range = 0;
	int distance = 0;
	Vector2D velocity;

};