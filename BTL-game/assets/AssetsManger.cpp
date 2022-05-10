
#include"AssetsManager.h"
#include"../ECS/Components.h"

const int enemy0_size[2] = { 72,45 };
const int enemy1_size[2] = { 72,33 };

AssetsManager::AssetsManager(Manager* man): manager(man)
{}


AssetsManager::~AssetsManager()
{

}


void AssetsManager::AddText(std::string id, const char* path)
{
	textures.emplace(id, loadTexture(path));
}


void AssetsManager::CreateProjectile(Vector2D pos, int range, int speed, std::string id , Vector2D vel)
{

	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, title_size, title_size, 1);
	projectile.addComponent<SpriteComponent>("projectile", false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectitles);

}


void AssetsManager::CreateEnemies(Vector2D pos, int range, int speed, std::string id, Vector2D vel)
{
	auto& enemy(manager->addEntity());
	enemy.addComponent<TransformComponent>(pos.x, pos.y, 72, 64 , 1);
	enemy.addComponent<SpriteComponent>(id, false);
	enemy.addComponent<Enemy>(range, speed, vel , pos);
	enemy.addComponent<ColliderComponent>(id);
	enemy.addGroup(Game::groupEnemies);
}





SDL_Texture* AssetsManager::GetTexture(std::string id)
{
	return textures[id];
}