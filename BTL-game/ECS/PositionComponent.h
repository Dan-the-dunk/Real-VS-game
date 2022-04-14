#pragma once

#include"Components.h"

class PositionComponent : public Component
{
public:

	PositionComponent(int x, int y) {
		xpos = x;
		ypos = y;
	}
	PositionComponent() {
		xpos = 0;
		ypos = 0;
	}

	int getXpos() { return xpos; };
	int getYpos() { return ypos; };


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
	int xpos, ypos;

};
