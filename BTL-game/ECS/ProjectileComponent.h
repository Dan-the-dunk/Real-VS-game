#pragma once


#include"ECS.h"
#include"Components.h"

class ProjectileComponent : public Component
{
public:

	ProjectileComponent(int rng , int sp  )
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
		if (distance > range)
		{
			cout << "Project ran out of range" << endl;
			entity->destroy();
		}

		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y 
			)
		{
			entity->destroy();
		}

	}
private:
	TransformComponent* transform;

	int speed, range, distance;


};