#pragma once


#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"



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

		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y 
			)
		{
			cout << "out of window" << endl;
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