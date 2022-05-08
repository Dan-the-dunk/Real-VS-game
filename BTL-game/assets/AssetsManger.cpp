
#include"AssetsManager.h"

AssetsManager::AssetsManager(Manager* man): manager(man)
{}


AssetsManager::~AssetsManager()
{

}


void AssetsManager::AddText(std::string id, const char* path)
{
	textures.emplace(id, loadTexture(path));
}

SDL_Texture* AssetsManager::GetTexture(std::string id)
{
	return textures[id];
}