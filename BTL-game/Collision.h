#pragma once
#include"SDL.h"


class ColliderComponent;



class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);


	static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);

	
	static bool AABB_OT(const SDL_Rect& rectA, const SDL_Rect& rectB, int vel_y);
	

	static bool on_top ;

};