#pragma once

#include<map>
#include<string>
#include"TextureManager.h"
#include"../Physics/Vector2D.h"
#include"../ECS/ECS.h"
#include<SDL_ttf.h>
class AssetsManager
{
public:

	AssetsManager(Manager* man);
	~AssetsManager();

	//gameobjects

	void CreateProjectile(Vector2D pos, int range, int speed, std::string id , Vector2D vel);

	void CreateEnemies(Vector2D pos, int range, int speed, std::string id, Vector2D vel);

	//text manager

	void AddText(std::string id, const char* path);

	void AddFont(std::string id, std::string path, int font_size);

	TTF_Font* getFont(std::string id);


	SDL_Texture* GetTexture(std::string id);
private:
	Manager* manager;

	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;

};