#pragma once


#include"Components.h"
#include<SDL.h>
#include"D:\visual c++\BTL-game Loop\BTL-game/SDL_Ultis.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		texture = loadTexture(path);
	}
	void init() override
	{
		position = &entity->getComponent<PositionComponent>();
		srcRect = { 0,0,140,140 };
		desRect.w = 140;
		desRect.h = 140;
	}
	void update() override
	{
		desRect.x = position->getXpos();
		desRect.y = position->getYpos();

	}
	void draw() override
	{
		drawTexture(texture, srcRect, desRect);
	}
};

