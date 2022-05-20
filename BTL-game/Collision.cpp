#include"Collision.h"
#include"ECS/ColliderComponent.h"



bool Collision::on_top = false;

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {

	on_top = false;

	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{

		if (rectA.x + rectA.w - 4 >= rectB.x &&
			rectB.x + rectB.w - 4 >= rectA.x &&
			rectA.y + rectA.h >= rectB.y)
		{
			cout << "on top " << endl;
			on_top = true;
		}
		return  true;
	}
		

	return false;
}



bool Collision::AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB)
{
	if (AABB(colliderA.collider, colliderB.collider))
	{
		std::cout << colliderA.tag << " hit " << colliderB.tag<<endl;
		return true;
	}
	else {
		return false;
	}
}

