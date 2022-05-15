#include"playState.h"
#include<SDL.h>
#include"Game.h"
#include"Gamestate.h"
#include"gameoverState.h"
#include"menuState.h"
#include"assets/TextureManager.h"
#include"Map.h"
#include"ECS/ECS.h"
#include"ECS/Components.h"
#include"Physics/Vector2D.h"
#include"Collision.h"
#include<cmath>
#include"assets/AssetsManager.h"
#include<format>
#include<sstream>




CPlayState CPlayState::m_PlayState;

//bool CPlayState::game_over = false;

using namespace std;

Map* maplv1 = nullptr;
Manager manager;

AssetsManager* CPlayState::assets = new AssetsManager(&manager);


SDL_Rect CPlayState::camera = { 0,0,SCREEN_WIDTH  , SCREEN_HEIGHT };

SDL_Event CPlayState::ev;


auto& newPlayer(manager.addEntity());
auto& label(manager.addEntity());
auto& hp_text(manager.addEntity());


void CPlayState::Init()
{
	
	// 1 ham de load data cho lv ?:

	//cac data load 1 lan.
	//if lv change , o load lai nua.



	bg = loadTexture("assets/image/menu.png");

	backgroundTxt = loadTexture(backGroundImagePath);
	gameOverTxt = loadTexture(gameOverImagePath);
	
	assets->AddText("enemy0", "assets/enemies/e0.png");
	assets->AddText("enemy", "assets/image/rl_projectile.jpg");
	assets->AddText("enemy1", "assets/enemies/e1.png");
	assets->AddText("player", "assets/image/dirt_txt.png");
	assets->AddText("projectile", "assets/image/rl_projectile.jpg");

	assets->AddFont("arial", "assets/arial.ttf", 16);
	

	//str = format("number {} , number {}", 1, 2);


	



	//load component(pos , sprite)

	maplv1 = new Map("assets/tileset_items.png", 1, 32, 90, 40);
	//qua ton ram, nen de background thi hon/.

	if(current_lv == 1) maplv1->loadmap("assets/map_enemies.map");
	else if (current_lv == 2) maplv1->loadmap("assets/map_lv2.map");
	// file lv du 2 data tren.


	//label
	SDL_Color white = { 255,255,255,255 };

	if(! label.hasComponent<UILabel>())
	{
		hp_text.addComponent<UILabel>(SCREEN_WIDTH/2, 10, "HP", "arial", white);
		label.addComponent<UILabel>(10, 10, "NAHHH", "arial", white);
	}
	

	label.addGroup(groupLabels);
	hp_text.addGroup(groupLabels);


	//thu picture perfect
	newPlayer.addComponent<TransformComponent>(32, 32);
	newPlayer.addComponent<SpriteComponent>("player", false);
	newPlayer.addComponent<RigidBody>(1);
	newPlayer.addComponent<Stats>();
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);



	printf("CPlayState Init\n");

	cout << "load lv" << current_lv << endl;
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



auto& players(manager.getGroup(CPlayState::groupPlayers));
auto& colliders(manager.getGroup(CPlayState::groupColliders));
auto& projectiles(manager.getGroup(CPlayState::groupProjectitles));
auto& enemies(manager.getGroup(CPlayState::groupEnemies));
auto& labels(manager.getGroup(CPlayState::groupLabels));


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
						newPlayer.getComponent<RigidBody>().bouncing_back = false;
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

							newPlayer.getComponent<Stats>().hp += f_gain/2;

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



	Vector2D pos = newPlayer.getComponent<TransformComponent>().position;
	Vector2D vel = newPlayer.getComponent<TransformComponent>().velocity;


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

	SDL_Rect fart_rect = newPlayer.getComponent<ColliderComponent>().desR;

	fart_rect.x += 32;

	for (auto e : enemies)
	{


		
		if (Collision::AABB(fart_rect, e->getComponent<ColliderComponent>().collider))
		{

			e->getComponent<Enemy>().hp -= 2;
		}


		Collision::on_top = false;

		if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, e->getComponent<ColliderComponent>().collider))
		{
			

			

			//wriet a function. newpla
			if (Collision::on_top)
			{
				newPlayer.getComponent<TransformComponent>().velocity.y = -14;
				e->getComponent<Enemy>().hp -= 2;
			}

			else
			{
				

				bounce_back(newPlayer.getComponent<TransformComponent>().velocity);
				newPlayer.getComponent<RigidBody>().bouncing_back = true;
				newPlayer.getComponent<RigidBody>().setFraction(Vector2D(-0.2f, 0));
			}
			//
			
			if (e->getComponent<Enemy>().hp <= 0) e->destroy();

			// newPlayer.getComponent<Stats>().hp--;

			
			//e->destroy();
		}
	}


	stringstream ss;
	ss << "Player Position :" << newPlayer.getComponent<TransformComponent>().position;
	
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	ss.str("");

	ss << "Player HP : " << newPlayer.getComponent<Stats>().hp;
	hp_text.getComponent<UILabel>().SetLabelText(ss.str(), "arial");

	

	
	updateCam(newPlayer.getComponent<TransformComponent>().position.x, newPlayer.getComponent<TransformComponent>().position.y , maplv1->mapXmax , maplv1->mapYmax);
	
	



	if (newPlayer.getComponent<Stats>().hp <= 0)
	{
		game->ChangeState(CGameoverState::Instance());
	}


	if (newPlayer.getComponent<TransformComponent>().position.x >= maplv1->mapXmax - 200)
	{
		current_lv++;
		delete maplv1;
		game->ChangeState(CPlayState::Instance());
		
		
	}
	

	
	


}

void CPlayState::Draw(Game* game)

{

	SDL_RenderClear(Game::gRenderer);

	maplv1->drawMap(newPlayer.getComponent<TransformComponent>().velocity.x);


	

	for (auto& p : players)
	{
		p->draw();


		SDL_SetRenderDrawColor(Game::gRenderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(Game::gRenderer, & (newPlayer.getComponent<Stats>().fart_box ) );
	}
	
	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
	
		e->getComponent<ColliderComponent>().collider.x = e->getComponent<ColliderComponent>().collider.x - camera.x;
		e->getComponent<ColliderComponent>().collider.y = e->getComponent<ColliderComponent>().collider.y - camera.y;
		SDL_Rect eRect = e->getComponent<ColliderComponent>().desR;
		SDL_SetRenderDrawColor(Game::gRenderer,255, 0, 0, 255);
		SDL_RenderDrawRect(Game::gRenderer, &eRect);

		e->draw();
	}


	

	for (auto& l : labels)
	{
	
		l->draw();
	}
	

	SDL_RenderPresent(Game::gRenderer);


	
}





