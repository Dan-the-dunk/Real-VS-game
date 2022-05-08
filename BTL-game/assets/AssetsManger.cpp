
#include"AssetsManager.h"
#include "../ECS/Components.h"

AssetsManager::AssetsManager(Manager* man): manager(man)
{}


AssetsManager::~AssetsManager()
{

}


void AssetsManager::AddText(std::string id, const char* path)
{
	textures.emplace(id, loadTexture(path));
}

void AssetsManager::CreateProjectile(Vector2D pos, int range, int speed, std::string id)
{

	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>("pro_test", false);
	projectile.addComponent<ProjectileComponent>(range, speed);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectitles);

}



SDL_Texture* AssetsManager::GetTexture(std::string id)
{
	return textures[id];
}