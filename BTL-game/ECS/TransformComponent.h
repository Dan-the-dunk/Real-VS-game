#pragma once

#include"Components.h"
#include"../Physics/Vector2D.h"
//testing zone



class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	
	int height = 119;
	int width = 72;
	float scale = 1 ;

	const int speed = 4;

	TransformComponent(float x, float y) 
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int w, int h)
	{
		width = w;
		height = h;
	}

	TransformComponent(float x, float y, int w, int h , float scale)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
	}

	TransformComponent(float sc)
	{
		scale = sc;
	}

	TransformComponent() 
	{
		position.zero();
	}

	
	void init() override
	{
		velocity.zero();
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

// khu de variable

