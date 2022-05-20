
#include"AssetsManager.h"
#include"../ECS/Components.h"

const int enemy0_size[2] = { 45,45 };
const int enemy1_size[2] = { 40,33 };
const int num_of_sprites = 6;

AssetsManager::AssetsManager(Manager* man): manager(man)
{}


AssetsManager::~AssetsManager()
{

}


void AssetsManager::AddText(std::string id, const char* path)
{
	textures.emplace(id, loadTexture(path));
}


void AssetsManager::CreateProjectile(Vector2D pos, int range, int speed, std::string id , Vector2D vel )
{

	auto& projectile(manager->addEntity());
	//magic number
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 12, 8, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel, id);
	projectile.addComponent<ColliderComponent>(id);
	projectile.addGroup(CPlayState::groupProjectitles);

}


void AssetsManager::CreateEnemies(Vector2D pos, int range, int speed, std::string id, Vector2D vel)
{
	int height = 0, width = 0 ;

	if (id == "enemy0")
	{
		height = enemy0_size[1];
		width = enemy0_size[0];
	}
	if (id == "enemy1")
	{
		height = enemy1_size[1];
		width = enemy1_size[0];
	}
	auto& enemy(manager->addEntity());
	enemy.addComponent<TransformComponent>(pos.x, pos.y - height + title_size, width, height , 1);
	enemy.addComponent<SpriteComponent>(id, true , 6);
	enemy.addComponent<Enemy>(range, speed, vel , pos , id);
	enemy.addComponent<ColliderComponent>(id );
	enemy.addGroup(CPlayState::groupEnemies);
}





SDL_Texture* AssetsManager::GetTexture(std::string id)
{
	return textures[id];
}


void AssetsManager::AddFont(std::string id, string path, int font_size)
{
	fonts.emplace(id, TTF_OpenFont( (path.c_str()) , font_size )) ;
}


TTF_Font* AssetsManager::getFont(std::string id)
{
	return fonts[id];
}


