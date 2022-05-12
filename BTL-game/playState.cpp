#include"playState.h"
#include<SDL.h>
#include"Game.h"
#include"Gamestate.h"
#include"menuState.h"
#include"assets/TextureManager.h"
#include"Map.h"
#include"ECS/Components.h"
#include"Physics/Vector2D.h"
#include"Collision.h"
#include<cmath>
#include"assets/AssetsManager.h"
#include<format>






using namespace std;

Map* maplv1 = nullptr;
Manager manager;

AssetsManager* CPlayState::assets = new AssetsManager(&manager);


SDL_Rect CPlayState::camera = { 0,0,SCREEN_WIDTH  , SCREEN_HEIGHT };

SDL_Event CPlayState::ev;


auto& newPlayer(manager.addEntity());




void CPlayState::Init()
{
	bg = loadTexture("assets/image/menu.png");

	printf("CPlayState Init\n");


	//init a whole lotta shit . 
}

void CPlayState::Cleanup()
{
	SDL_DestroyTexture(bg);

	printf("CPlayState Cleanup\n");
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
}





void CPlayState::loadMedia()
{
	backgroundTxt = loadTexture(backGroundImagePath);
	gameOverTxt = loadTexture(gameOverImagePath);

	//str = format("number {} , number {}", 1, 2);


	assets->AddText("enemy0", "assets/enemies/e0.png");

	assets->AddText("enemy", "assets/image/rl_projectile.jpg");

	assets->AddText("enemy1", "assets/enemies/e1.png");
	assets->AddText("player", "assets/image/dirt_txt.png");
	assets->AddText("projectile", "assets/image/rl_projectile.jpg");



	//load component(pos , sprite)

	maplv1 = new Map("assets/tileset_items.png", 1, 32, 90, 40);
	//qua ton ram, nen de background thi hon/.

	maplv1->loadmap("assets/map_enemies.map");


	//thu picture perfect
	newPlayer.addComponent<TransformComponent>(32, 32);
	newPlayer.addComponent<SpriteComponent>("player", false);
	newPlayer.addComponent<RigidBody>(1);
	newPlayer.addComponent<Stats>();
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);


	assets->CreateEnemies(Vector2D(600, 600), 200, 2, "enemy0", Vector2D(1, 0));

}

auto& players(manager.getGroup(CPlayState::groupPlayers));
auto& colliders(manager.getGroup(CPlayState::groupColliders));
auto& projectiles(manager.getGroup(CPlayState::groupProjectitles));
auto& enemies(manager.getGroup(CPlayState::groupEnemies));



void checkCollsionMap(Map* map)
{

	//->map[0] check lai thanh map[i];
	bool check_onground = false;
	// 3 = const num ;

	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	Vector2D pos = newPlayer.getComponent<TransformComponent>().position;
	Vector2D vel = newPlayer.getComponent<TransformComponent>().velocity;




	int cWidth = newPlayer.getComponent<TransformComponent>().width;
	int cHeight = newPlayer.getComponent<TransformComponent>().height;




	for (int i = 0; i < 3; i++)
	{



		if (i == 0)
		{
			newPlayer.getComponent<RigidBody>().onground = false;

			// check vertical


			int min_width = cWidth > map->tileSize ? map->tileSize : cWidth;

			x1 = (pos.x) / map->tileSize;
			x2 = (pos.x + min_width) / map->tileSize;

			y1 = (pos.y + vel.y) / map->tileSize;
			y2 = (pos.y + vel.y + cHeight) / map->tileSize;

			if (x1 >= 0 && x2 <= map->sizeX && y1 >= 0 && y2 <= map->sizeY)
			{
				if (vel.y >= 0)
				{

					if (map->map[0].cMap[y2][x1] != map->BLANK_TILE || map->map[0].cMap[y2][x2] != map->BLANK_TILE)
					{
						pos.y = y2 * map->tileSize;
						pos.y -= cHeight;
						vel.y = 0;
						newPlayer.getComponent<RigidBody>().onground = true;
					}
				}

				else if (vel.y < 0)
				{
					if (map->map[0].cMap[y1][x1] != map->BLANK_TILE || map->map[0].cMap[y1][x2] != map->BLANK_TILE)
					{
						pos.y = (y1 + 1) * map->tileSize;
						vel.y = 0;
					}
				}



			}




			x1 = (pos.x + vel.x) / map->tileSize;
			x2 = (pos.x + vel.x + cWidth - 1) / map->tileSize;

			int min_height = cHeight > map->tileSize ? map->tileSize : cHeight;

			y1 = (pos.y) / map->tileSize;
			y2 = (pos.y + min_height - 1) / map->tileSize;



			if (x1 >= 0 && x2 <= map->sizeX && y1 >= 0 && y2 <= map->sizeY)
			{
				if (vel.x > 0)
				{
					//check move right
					if (map->map[0].cMap[y1][x2] != map->BLANK_TILE || map->map[0].cMap[y2][x2] != map->BLANK_TILE)
					{
						pos.x = x2 * map->tileSize;
						pos.x -= cWidth + 1;
						vel.x = 0;

					}
				}
				else if (vel.x < 0)
				{
					//check move right
					if (map->map[0].cMap[y1][x1] != map->BLANK_TILE || map->map[0].cMap[y2][x1] != map->BLANK_TILE)
					{
						pos.x = (x1 + 1) * map->tileSize;
						vel.x = 0;

					}
				}
			}


			if (pos.x < 0) pos.x = 0;
			else if (pos.x + cWidth >= map->sizeX * map->tileSize) pos.x = map->sizeX * map->tileSize - cWidth - 1;




			//test operator overload

			newPlayer.getComponent<TransformComponent>().position = pos;

			newPlayer.getComponent<TransformComponent>().velocity = vel;
		}

		if (i == 1)
		{
			x1 = (pos.x) / map->tileSize;
			x2 = (pos.x + cWidth) / map->tileSize;

			y1 = (pos.y) / map->tileSize;
			y2 = (pos.y + cHeight) / map->tileSize;



			if (x1 >= 0 && x2 <= map->sizeX && y1 >= 0 && y2 <= map->sizeY)

			{
				for (int y = y1; y <= y2; y++)
				{
					for (int x = x1; x <= x2; x++)
					{
						if (map->map[1].cMap[y][x] != map->BLANK_TILE)
						{
							int f_gain = map->map[1].cMap[y][x] - 50 + 1;
							f_gain *= 12;
							newPlayer.getComponent<Stats>().fart_lv += f_gain;
							cout << newPlayer.getComponent<Stats>().fart_lv << endl;
							map->map[1].cMap[y][x] = map->BLANK_TILE;

							//play noise.//

						}
					}
				}
			}
		}

	}



}



void CPlayState::HandleEvents(Game* game)
{
	

	if (SDL_PollEvent(&ev)) {
		switch (ev.type) {
		case SDL_QUIT:
			Game::isRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			case SDLK_m:
				game->PushState(CMenuState::Instance());
				break;
			}
			break;
		}
	}
}

void CPlayState::Update(Game* game)
{


	manager.refresh();




	manager.update();



	checkCollsionMap(maplv1);


	for (auto p : projectiles)
	{
		if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			cout << "Hit projectile" << endl;
			p->destroy();
		}

		//Stats change, components.\
		//Add diff type for projectile for diff effects
	}




	camera.x = newPlayer.getComponent<TransformComponent>().position.x - SCREEN_WIDTH / 2; // gioi han vi tri nhan vat.
	camera.y = newPlayer.getComponent<TransformComponent>().position.y - SCREEN_HEIGHT / 2;


	//Camera( can sua lai cho fit map to hon.
	if (camera.x < 0) camera.x = 0;// 0 tac dong gi
	if (camera.x > maplv1->mapXmax - SCREEN_WIDTH) camera.x = maplv1->mapXmax - SCREEN_WIDTH;
	if (camera.y < 0) camera.y = 0;// 0 tac dong gi
	if (camera.y > maplv1->mapYmax - SCREEN_HEIGHT) camera.y = maplv1->mapYmax - SCREEN_HEIGHT;

}

void CPlayState::Draw(Game* game)

{

	SDL_RenderClear(Game::gRenderer);

	maplv1->drawMap(newPlayer.getComponent<TransformComponent>().velocity.x);



	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		//draw hit box;
		/*e->getComponent<ColliderComponent>().collider.x = e->getComponent<ColliderComponent>().collider.x - camera.x;
		e->getComponent<ColliderComponent>().collider.y = e->getComponent<ColliderComponent>().collider.y - camera.y;
		SDL_Rect eRect = e->getComponent<ColliderComponent>().collider;
		SDL_SetRenderDrawColor(gRenderer,255, 0, 0, 255);
		SDL_RenderDrawRect(gRenderer, &eRect);*/

		e->draw();
	}

	

	SDL_RenderPresent(Game::gRenderer);


	
}

