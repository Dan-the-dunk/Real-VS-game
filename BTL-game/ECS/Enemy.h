#pragma once


#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"


class Enemy : public Component
{

public:

	Enemy(int rng, int sp, Vector2D vel, Vector2D pos) : range(rng), speed(sp), velocity(vel), OgPos(pos)
	{
	}

	~Enemy()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

	}

	void update() override
	{
		distance += transform->velocity.x;

		// ham cho quay dau.
		


		transform->position += velocity;

		if (abs(transform->position.x - OgPos.x) >= range)
		{
	
			//transform->velocity.x = - velocity.x;
			velocity.x = - velocity.x;
		}

		

	}
private:
	TransformComponent* transform;

	int speed = 0;
	int range = 0;
	int distance = 0;
	Vector2D OgPos;
	Vector2D velocity;
};
