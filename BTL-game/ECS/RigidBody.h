#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"

constexpr float GRAVITY = 2.0f;


class RigidBody : public Component 
{

public:
	
	static float CHAR_SIZE;
	
	RigidBody() = default;
	virtual  ~RigidBody() = default;


	RigidBody(float g) {
		gravity_scale = g;
	}

	void init() override {
		
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent < TransformComponent>();
		}
		transform = &entity->getComponent < TransformComponent>();
	}
	 
	void update() override 
	{

		// CHAR_SIZE *= (float)transform->scale; dung r nhung tai arnold o trung tam hinh nen bi chim xuong.

		//Thay doi true false;
		if ((transform->position.y + CHAR_SIZE*transform->scale < SCREEN_HEIGHT))
		{
			onground = false;
		}

		if (onground == false) {
			transform->velocity.y += gravity_scale * GRAVITY;
			//cout << "Not on ground" << endl;
		}


		if ((transform->position.y + transform->velocity.y * TransformComponent::speed < 0) ||
			(transform->position.y + CHAR_SIZE*transform->scale > SCREEN_HEIGHT))
		{
			//Move back a const gap
			transform->velocity.y = 0;
			transform->position.y = SCREEN_HEIGHT - CHAR_SIZE* transform->scale;
			
			onground = true;
			if (onground == true) cout << "Im on ground " << endl;
		}

	}

	bool onGround()
	{
		return onground;
	}




	void setForce(const Vector2D f) {
		force = f;
	}

private:
	bool onground = false;
	float gravity_scale = 1.0f;
	Vector2D drag = Vector2D();
	Vector2D force = Vector2D();
	TransformComponent* transform;
};



float RigidBody::CHAR_SIZE = 140;