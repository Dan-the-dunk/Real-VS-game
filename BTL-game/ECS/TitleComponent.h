#pragma once
#include"ECS.h"
#include"Components.h"
#include"TransformComponent.h"
#include"SpriteComponent.h"
#include<SDL.h>

class TitleComponenet : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	const char* path;

	SDL_Rect titleRect;
	int titleID;

	TitleComponenet() = default;

	TitleComponenet(int x, int y, int w, int h, int id) 
	{
		titleRect = { x, y,w,h };
		titleID = id;
	
		switch (titleID)
		{
			case 0:
				path = "assets/image/water_txt.png";
				break;

			case 1:
				path = "assets/image/grass_txt.png";
			break;

			case 2:
				path = "assets/image/dirt_txt.png";
				break;
			default:
				break;

		}
	
	}


	void init() override
	{
		entity->addComponent<TransformComponent>((float)titleRect.x, (float)titleRect.y, titleRect.w, titleRect.h , 1);
		transform = &entity->getComponent<TransformComponent>();
		
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();

	}



};