#pragma once
#include"ECS.h"
#include"Components.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"
#include<SDL.h>
#include"../assets/AssetsManager.h"


const char title_size = 32;

class TitleComponenet : public Component {
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	Vector2D position;


	TitleComponenet() = default;


	TitleComponenet(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = loadTexture(path);

		position.x = xpos;
		position.y = ypos;


		srcRect = { srcX, srcY , title_size , title_size };

		desRect = { xpos, ypos , title_size , title_size };


	}



	~TitleComponenet()
	{
		SDL_DestroyTexture(texture);
	}

	//Camera

	void update() override
	{
		desRect.x = position.x - Game::camera.x;
		desRect.y = position.y - Game::camera.y;
	}

	

	void draw() override
	{
		drawTexture(texture, srcRect, desRect, SDL_FLIP_NONE);
	}





};