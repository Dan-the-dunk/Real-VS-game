#pragma once
#include"ECS.h"
#include"Components.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"
#include<SDL.h>
#include"../assets/AssetsManager.h"
class TitleComponenet : public Component {
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;


	TitleComponenet() = default;


	TitleComponenet(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = loadTexture(path);

		srcRect = { srcX, srcY , 64 , 64 };

		desRect = { xpos, ypos , 64 , 64 };


	}



	~TitleComponenet()
	{
		SDL_DestroyTexture(texture);
	}

	

	void draw() override
	{
		drawTexture(texture, srcRect, desRect, SDL_FLIP_NONE);
	}





};