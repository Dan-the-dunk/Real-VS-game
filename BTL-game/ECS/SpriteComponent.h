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
	int frames = 0;
	int speed = 100;
	//Khu thu nghiem
	



public:
	SpriteComponent() = default;

	int animIndex = 0;
	
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* path)
	{
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

		//Camera.
		desRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		desRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		desRect.w = static_cast<int>(transform->width* transform->scale);
		desRect.h = static_cast<int>(transform->height* transform->scale);
	}
	void draw() override
	{
		drawTexture(texture, srcRect, desRect, spriteFlip);
	}


	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}


};

