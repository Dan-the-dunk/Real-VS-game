#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"

constexpr float GRAVITY = 0.7f;
const float max_fall_speed = 15;



class RigidBody : public Component 
{

public:
	
	const float CHAR_SIZE = 32; 
	bool onground = false;
	bool bounce_right;
	bool bouncing_back = false;


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
			transform->velocity.y += gravity_scale * GRAVITY ;

			
			if (transform->velocity.y >= max_fall_speed) transform->velocity.y = max_fall_speed;
			//cout << "Not on ground" << endl;
		}

		
		if (onground == true) {
			//cout << "Im on ground" << endl;

			float fraction_x = transform->velocity.x > 0 ? fraction.x : -fraction.x;

			float pre_vel = transform->velocity.x;

			transform->velocity.x += fraction_x;

			if (transform->velocity.x * pre_vel <= 0) fraction.x = 0;

		}

	}

	bool onGround()
	{
		return onground;
	}

	



	void setFraction(const Vector2D f) {
		fraction = f;
	}



private:

	
	int gravity_scale = 1;
	Vector2D drag = Vector2D();
	Vector2D fraction = Vector2D();
	TransformComponent* transform;
};



