#pragma once


#include"Components.h"
#include<SDL.h>
#include"../assets/AssetsManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

	bool animated = false;
	bool pAnimated = false;
	int frame = 0;
	int speed = 100;
	//Khu thu nghiem
	int spaceX = 0;
	int spaceY = 0;


public:
	SpriteComponent() = default;





	SpriteComponent(const char* path)
	{
		setText(path);
	}

	SpriteComponent(const char* path, int mFrames, int mSpeed , int mSpaceX, int mSpaceY )
	{
		pAnimated = true;
		frame = mFrames;
		speed = mSpeed;
		spaceX = mSpaceX;
		spaceY = mSpaceY;
		setText(path);
	}

	SpriteComponent(const char* path, int mFrames, int mSpeed)
	{
		animated = true;
		frame = mFrames;
		speed = mSpeed;
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

		//72,119 la info cua o dau tien phan walk;
		srcRect = { 0 ,119 ,72, 119};
		desRect.w = (int)transform->width;
		desRect.h = (int)transform->height;
	}
	void update() override
	{


		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frame );
		}




		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);
		desRect.w = static_cast<int>(transform->width* transform->scale);
		desRect.h = static_cast<int>(transform->height* transform->scale);
	}
	void draw() override
	{
		drawTexture(texture, srcRect, desRect);
	}
};

