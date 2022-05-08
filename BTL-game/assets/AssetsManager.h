#pragma once

#include<map>
#include<string>
#include"TextureManager.h"
#include"../Physics/Vector2D.h"
#include"../ECS/ECS.h"
#include"../ECS/Components.h"


class AssetsManager
{
public:

	AssetsManager(Manager* man);
	~AssetsManager();
	// gameobject;

	void CreateProjectile(Vector2D pos, int range, int speed, std::string id);
	


	//Texture manager
	void AddText(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;


};