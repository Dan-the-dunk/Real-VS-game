#pragma once

#include"Components.h"
#include"../Physics/Vector2D.h"
class TransformComponent : public Component
{
public:
	Vector2D position;


	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent() {
		position.x = 0;
		position.y = 0;
	}

	

	void update() override
	{
		
	}

	

};
