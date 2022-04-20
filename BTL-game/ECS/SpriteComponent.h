#pragma once


#include"Components.h"
#include<SDL.h>
#include"../assets/AssetsManager.h"
#include"Animation.h"
#include<map>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;

	bool animated = false;
	bool pAnimated = false;
	int frames = 0;
	int speed = 100;
	//Khu thu nghiem
	int spaceX = 0;
	int spaceY = 0;


public:
	SpriteComponent() = default;

	int animIndex = 0;
	
	std::map<const char*, Animation> animations;



	SpriteComponent(const char* path)
	{
		setText(path);
	}

	SpriteComponent(const char* path, int mFrames, int mSpeed , int mSpaceX, int mSpaceY )
	{
		pAnimated = true;
		frames = mFrames;
		speed = mSpeed;
		spaceX = mSpaceX;
		spaceY = mSpaceY;
		setText(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 1, 100);
		Animation walk = Animation(1, 7, 100);
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");


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
		srcRect = { 0 ,0 ,transform->width, transform->height};
		desRect.w = (int)transform->width;
		desRect.h = (int)transform->height;
	}
	void update() override
	{


		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames );
		}

		srcRect.y = animIndex * transform->height;


		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);
		desRect.w = static_cast<int>(transform->width* transform->scale);
		desRect.h = static_cast<int>(transform->height* transform->scale);
	}
	void draw() override
	{
		drawTexture(texture, srcRect, desRect);
	}


	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}


};

