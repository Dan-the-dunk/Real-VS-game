#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"

constexpr float GRAVITY = 2.0f;




class RigidBody : public Component 
{

public:
	
	const float CHAR_SIZE = 32; 
	bool onground = false;
	bool lockGround = false;


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



		if (onground == false) {
			transform->velocity.y += gravity_scale * GRAVITY;
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

	
	float gravity_scale = 1.0f;
	Vector2D drag = Vector2D();
	Vector2D force = Vector2D();
	TransformComponent* transform;
};



