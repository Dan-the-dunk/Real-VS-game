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

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setText(const char* path) {
		texture = loadTexture(path);
	}


	SDL_Rect getRect() {
		return desRect;
	}


	void init() override
	{
		
		

		transform = &entity->getComponent<TransformComponent>();
		srcRect = { 0,0,140,140 };
		desRect.w = (int)transform->width;
		desRect.h = (int)transform->height;
	}
	void update() override
	{
		desRect.x = (int)transform->position.x;
		desRect.y = (int)transform->position.y;
		desRect.w = (int)transform->width* transform->scale;
		desRect.h = (int)transform->height* transform->scale;
	}
	void draw() override
	{
		drawTexture(texture, srcRect, desRect);
	}
};

