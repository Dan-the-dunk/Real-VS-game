#pragma once

#include"Components.h"
#include"../Physics/Vector2D.h"
//testing zone

const int speed = 4;

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	



	TransformComponent(float x, float y) 
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent() 
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	
	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}


	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;


		/*/testing

		if ((position.y < 0) || (position.y + CHAR_SIZE > SCREEN_HEIGHT))
		{
			//Move back
			position.y -= velocity.y*speed;
		}

		*/


	}

	

};
