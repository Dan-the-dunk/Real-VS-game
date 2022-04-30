#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"

constexpr float GRAVITY = 1.0f;
const float max_fall_speed = 20;



class RigidBody : public Component 
{

public:
	
	const float CHAR_SIZE = 32; 
	bool onground = false;
	bool lockGround = false;


	RigidBody() = default;
	virtual  ~RigidBody() = default;


	RigidBody(int g) {
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
		


		if (onground == false) {
			transform->velocity.y += gravity_scale * GRAVITY;
			if (transform->velocity.y >= max_fall_speed) transform->velocity.y = max_fall_speed;
			cout << "Not on ground" << endl;
		}

		
		if (onground == true) {
			cout << "Im on ground" << endl;
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

	
	int gravity_scale = 1;
	Vector2D drag = Vector2D();
	Vector2D force = Vector2D();
	TransformComponent* transform;
};



