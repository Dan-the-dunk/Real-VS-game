#pragma once
#include<string>
#include"SDL.h"
#include"Components.h"

class ColliderComponent : public Component {
public:

	SDL_Rect collider;
	TransformComponent* transform;
	std::string tag;

	ColliderComponent(std::string t) {
		tag = t;
	}


	void init() override {
		//ktra if co entity
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();

		Game::colliders.push_back(this);

	}

	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = (int)(transform->width * transform->scale);
		collider.h = (int)(transform->height * transform->scale);
	}

};
