#pragma once
#include"ECS.h"
#include"Components.h"
#include"../Physics/Vector2D.h"

constexpr float GRAVITY = 2.0f;
const int CHAR_SIZE = 140;

class RigidBody : public Component 
{

public:
	
	

	RigidBody() = default;
	virtual  ~RigidBody() = default;


	RigidBody(float g) {
		gravity_scale = g;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}
	 
	void update() override 
	{
		//Thay doi true false;
		if ((transform->position.y + transform->velocity.y * speed + CHAR_SIZE < SCREEN_HEIGHT)) 
		{
			onground = false;
		}

		if (onground == false) {
			transform->velocity.y += gravity_scale * GRAVITY;
			cout << "Not on ground" << endl;
		}


		if ((transform->position.y + transform->velocity.y * speed < 0) || (transform->position.y + transform->velocity.y * speed + CHAR_SIZE > SCREEN_HEIGHT))
		{
			//Move back
			transform->position.y -= transform->velocity.y * speed;
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