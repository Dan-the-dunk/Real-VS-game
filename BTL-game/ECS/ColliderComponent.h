#pragma once
#include<string>
#include"SDL.h"
#include"Components.h"
#include"../Gamestate.h"
#include"../playState.h"
#include"../Game.h"

class ColliderComponent : public Component {
public:

	SDL_Rect collider;
	
	
	std::string tag;

	int size = 32;
	SDL_Rect srcR, desR;
	TransformComponent* transform;

	ColliderComponent(std::string t ,int size) {
		tag = t;

		desR.h = desR.w = size;
	}



	ColliderComponent(std::string t) {
		tag = t;

		

	}

	ColliderComponent(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}




	void init() override {
		//ktra if co entity
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();

		//tex = loadTexture("assets/col_txt.png");

		
		collider.w = static_cast<int>(transform->width) ;
		collider.h = static_cast<int>(transform->height) ;

		srcR = { 0, 0, 32, 32 };
		desR = { collider.x, collider.y, collider.w, collider.h };

		

	}



	void update() override
	{

		if (tag != "terrain")

		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			

	
		}
		


		desR.x = collider.x - CPlayState::camera.x;
		desR.y = collider.y - CPlayState::camera.y;
		

	}

	
private:

};
