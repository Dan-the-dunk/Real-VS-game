#pragma once
#include<string>
#include"SDL.h"
#include"Components.h"

class ColliderComponent : public Component {
public:

	SDL_Rect collider;
	
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, desR;
	TransformComponent* transform;

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

		tex = loadTexture("assets/col_txt.png");

		srcR = { 0, 0, 32, 32 };
		desR = { collider.x, collider.y, collider.w, collider.h };

		

	}



	void draw() override
	{
		drawTexture(tex, srcR, desR, SDL_FLIP_NONE);
	}


	void update() override
	{

		if (tag != "terrain")

		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = (int)(transform->width * transform->scale);
			collider.h = (int)(transform->height * transform->scale);
		}
		


		desR.x = collider.x - Game::camera.x;
		desR.y = collider.y - Game::camera.y;
	}
private:

};
