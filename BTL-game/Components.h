#pragma once
#include"ECS.h"

class PositionComponent : public Component
{
public:

	int getXpos() { return xpos; };
	int getYpos() { return ypos; };

	void init() override
	{
		xpos = 0;
		ypos = 0;
	}
	void update() override
	{
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) 
	{
		xpos = x;
		ypos = y;
	}

private:
	int xpos , ypos;

};