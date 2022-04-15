#pragma once


#include"Components.h"
#include<SDL.h>
#include"../SDL_Ultis.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

public:
	SpriteComponent() = default;

	SpriteComponent(const char* path)
	{
		setText(path);
	}

	void setText(const char* path) {
		texture = loadTexture(path);
	}


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect = { 0,0,140,140 };
		desRect.w = 140;
		desRect.h = 140;
	}
	void update() override
	{
		desRect.x = (int)transform->position.x;
		desRect.y = (int)transform->position.y;

	}
	void draw() override
	{
		drawTexture(texture, srcRect, desRect);
	}
};

