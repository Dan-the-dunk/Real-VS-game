#pragma once

struct Animation
{
	int index;
	int speed;
	int frames;

	Animation(){}

	Animation(int i, int f, int s)
	{
		index = i;
		speed = s;
		frames = f;

	}
};