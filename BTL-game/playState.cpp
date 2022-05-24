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
#include"Timer.h"

//test timer

const int max_lv = 2;

int CPlayState::current_lv = 1;
bool CPlayState::gameOver = false;

Mix_Music* CPlayState::bgm = nullptr;
Mix_Music* rick = nullptr;
Mix_Chunk* CPlayState::jump = nullptr;
Mix_Chunk* CPlayState::get_hit = nullptr;
Mix_Chunk* CPlayState::die = nullptr;
Mix_Chunk* CPlayState::fart = nullptr;
Mix_Chunk* CPlayState::strong_fart = nullptr;

GTimer gTimer;

CPlayState CPlayState::m_PlayState;

//bool CPlayState::game_over = false;

Vector2D a, b;

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

	gameOver = false;
	

	
	// 1 ham de load data cho lv ?:

	//cac data load 1 lan.
	//if lv change , o load lai nua.



	string spritesheet = format("assets/terrain{}.png",current_lv);
	string map_link = format("assets/map_lv{}.map",current_lv);


	bg = loadTexture("assets/image/menu.png");

	backgroundTxt = loadTexture(backGroundImagePath);
	gameOverTxt = loadTexture(gameOverImagePath);
	
	assets->AddText("enemy0", "assets/enemies/e0_f.png");
	assets->AddText("enemy", "assets/image/rl_projectile.jpg");
	assets->AddText("enemy1", "assets/enemies/e1_f.png");
	assets->AddText("player", "assets/image/petersprite.png");
	assets->AddText("projectile", "assets/image/ball.png");
	assets->AddText("e_projectile1", "assets/image/ball.png");
	assets->AddText("e_projectile1_m", "assets/image/ball.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);
	

	
	maplv1 = new Map(spritesheet.c_str(), 1, 32, 120, 40);
	maplv1->loadmap(map_link);



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
	
	
	newPlayer.addComponent<TransformComponent>(48, 61);
	newPlayer.addComponent<SpriteComponent>("player",true);
	newPlayer.addComponent<RigidBody>(1);
	newPlayer.addComponent<Stats>();
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	
	newPlayer.addGroup(groupPlayers);




	

	jump = Mix_LoadWAV("assets/music/jump.wav");
	fart = Mix_LoadWAV("assets/music/fart.wav");
	
	strong_fart = Mix_LoadWAV("assets/music/strong_fart.wav");


	bgm = Mix_LoadMUS("assets/music/bgm_F.wav");
	rick = Mix_LoadMUS("assets/music/rick.mp3");

	Mix_PlayMusic(bgm, -1);



	gTimer.isntLast();
	

	printf("CPlayState Init\n");

	cout << "load lv" << current_lv << endl;
	//init a whole lotta shit . 
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


void hit_spike(Vector2D& vel)
{
	//newPlayer.getComponent<Stats>().hp -= 1;
	if (newPlayer.getComponent<RigidBody>().onground == true)
	{
		vel.y = -12;
		newPlayer.getComponent<Stats>().hp--;
	}
}	


void checkCollsionMap(Map* map , Game* game)
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


	if (pos.y >= map->mapYmax)
	{
		CPlayState::gameOver = true;
	}


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

						if (map->map[0].cMap[y2][x1]/10 == map->SPIKE_TILES || map->map[0].cMap[y2][x2]/10 == map->SPIKE_TILES) hit_spike(vel);

						if (map->map[0].cMap[y2][x1] >= map->WATER_TILE_s && map->map[0].cMap[y2][x1] <= map->WATER_TILE_e ||
							map->map[0].cMap[y2][x2] >= map->WATER_TILE_s && map->map[0].cMap[y2][x2] <= map->WATER_TILE_e)
						{
							CPlayState::gameOver = true;
						}
						
					}
				}

				else if (vel.y <= 0)
				{

			
					if (map->map[0].cMap[y1][x1] != map->BLANK_TILE || map->map[0].cMap[y1][x2] != map->BLANK_TILE)
					{
						pos.y = (y1 + 1) * map->tileSize;
						vel.y = 0;
						if (map->map[0].cMap[y1][x1] / 10 == map->SPIKE_TILES || map->map[0].cMap[y1][x2] / 10 == map->SPIKE_TILES) hit_spike(vel);


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
						
						if (map->map[0].cMap[y1][x2] / 10 == map->SPIKE_TILES || map->map[0].cMap[y2][x2] / 10 == map->SPIKE_TILES) hit_spike(vel);
					}
				}
				else if (vel.x < 0)
				{
					//check move right
					if (map->map[0].cMap[y1][x1] != map->BLANK_TILE || map->map[0].cMap[y2][x1] != map->BLANK_TILE)
					{
						pos.x = (x1 + 1) * map->tileSize;
						vel.x = 0;
						
						if (map->map[0].cMap[y1][x1] / 10 == map->SPIKE_TILES || map->map[0].cMap[y2][x1] / 10 == map->SPIKE_TILES) hit_spike(vel);


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


						if (map->map[1].cMap[y][x] == map->NEXT_LV)
						{

							
							
							CPlayState::current_lv++;
							if (CPlayState::current_lv > max_lv)

							{
								cout << "reset lv" << endl;
								CPlayState::current_lv = 1;
								game->ChangeState(CGameoverState::Instance(true));
							}

							else
							{
								game->ChangeState(CPlayState::Instance());

							}
							
							

						}

						if (map->map[1].cMap[y][x] == map->RICK)
						{
							map->map[1].cMap[y][x] = map->BLANK_TILE;
							
							Mix_PlayMusic(rick, -1);
							std::cout << Mix_GetError() << endl;
							std::cout << "Play rick roll";
							
						}


						else if (map->map[1].cMap[y][x]/10 == map->FOOD_TILES && map->map[1].cMap[y][x] != maplv1->RICK)
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
				if (Mix_PausedMusic != 0)
				{
					Mix_PauseMusic();
				}
				
				break;
			case SDLK_c:
				cout << "con cu" << endl;

				break;
			}
			

			break;
		}
	}
}

void CPlayState::Update(Game* game)
{

	Vector2D prev_vel = newPlayer.getComponent<TransformComponent>().velocity;



	manager.refresh();
	manager.update();

	checkCollsionMap(maplv1, game);

	

	
	if (newPlayer.getComponent<Stats>().hp <= 0)
	{


		if (!gTimer.isLast())
		{
			gTimer.start();
			gTimer.last();
			gameOver = true;
			newPlayer.getComponent<SpriteComponent>().play("Die");
			newPlayer.getComponent<ColliderComponent>().collider = {0,0,0,0};
		}


		if (gTimer.getTicks() >= 2000)
		{
		
			
			game->ChangeState(CGameoverState::Instance(false));
		}
	}

	else
	{

		int cnt = 0;
		int c = 0;
		Vector2D pos = newPlayer.getComponent<TransformComponent>().position;
		Vector2D vel = newPlayer.getComponent<TransformComponent>().velocity;

	

		Vector2D vel_e;

		for (auto& p : projectiles)

		{
			c++;

			p->getComponent<ProjectileComponent>().getPlayerMove(pos);


			if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
			{
				cout << "Hit projectile" << endl;

				newPlayer.getComponent<Stats>().hp--;

				p->destroy();
			}


		}

	
		




		for (auto& e : enemies)
		{

			e->getComponent<Enemy>().getPlayerMove(pos, vel);


			Collision::on_top = false;

			if (e->getComponent<Enemy>().hp > 0)
			{
				if (Collision::AABB_OT(newPlayer.getComponent<ColliderComponent>().collider, e->getComponent<ColliderComponent>().collider, vel.y))
				{

					// newPlayer.getComponent<Stats>().hp--;
					vel_e = e->getComponent<Enemy>().velocity;


					cout << "Truoc up e p " << newPlayer.getComponent<TransformComponent>().velocity.y << endl;

					if (vel_e.x - vel.x > 0) newPlayer.getComponent<RigidBody>().bounce_right = true;
					else if (vel_e.x - vel.x < 0) newPlayer.getComponent<RigidBody>().bounce_right = false;

					cout << "Collider e " << e->getComponent<ColliderComponent>().collider.y << endl;
					cout << "Collider p " << newPlayer.getComponent<ColliderComponent>().collider.y << endl;

					if (Collision::on_top)
					{
						newPlayer.getComponent<TransformComponent>().position.y = e->getComponent<ColliderComponent>().collider.y - newPlayer.getComponent<TransformComponent>().height - 1;
						newPlayer.getComponent<TransformComponent>().velocity.y = -12;
						e->getComponent<Enemy>().hp -= 2;
					}

					else
					{

						newPlayer.getComponent<Stats>().hp--;
						bounce_back(newPlayer.getComponent<TransformComponent>().velocity, newPlayer.getComponent<RigidBody>().bounce_right);
						newPlayer.getComponent<RigidBody>().bouncing_back = true;
						newPlayer.getComponent<RigidBody>().setFraction(Vector2D(-0.2f, 0));
					}


					cout << "sau up e p " << newPlayer.getComponent<TransformComponent>().velocity.y << endl;

				}
			}
			

		}

		updateCam(newPlayer.getComponent<TransformComponent>().position.x, newPlayer.getComponent<TransformComponent>().position.y, maplv1->mapXmax, maplv1->mapYmax);




		if (gameOver)
		{

			delete maplv1;
			SDL_Delay(500);
			game->ChangeState(CGameoverState::Instance(false));

		}


		if (vel.x * prev_vel.x <= 0)
		{
			newPlayer.getComponent<RigidBody>().setFraction(Vector2D(0, 0));
			if (vel_e.x != 0)
			{
				newPlayer.getComponent<RigidBody>().setFraction(Vector2D(-0.2, 0));
			}
		}

		
		
	

	}
	
	


}

void CPlayState::Draw(Game* game)

{

	SDL_RenderClear(Game::gRenderer);

	maplv1->drawMap(newPlayer.getComponent<TransformComponent>().velocity.x);


	

	for (auto& p : players)
	{
		p->draw();

		/*
		SDL_Rect fart_collider = newPlayer.getComponent<Stats>().fart_box;

		fart_collider.x -= camera.x;
		fart_collider.y -= camera.y;

		SDL_SetRenderDrawColor(Game::gRenderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(Game::gRenderer, & (fart_collider) ) ;*/
	}
	
	for (auto& p : projectiles)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
	
		/*
		e->getComponent<ColliderComponent>().collider.x = e->getComponent<ColliderComponent>().collider.x - camera.x;
		e->getComponent<ColliderComponent>().collider.y = e->getComponent<ColliderComponent>().collider.y - camera.y;
		SDL_Rect eRect = e->getComponent<ColliderComponent>().desR;
		SDL_SetRenderDrawColor(Game::gRenderer,255, 0, 0, 255);
		SDL_RenderDrawRect(Game::gRenderer, &eRect);
		*/

		e->draw();
	}


	

	for (auto& l : labels)
	{
	
		l->draw();
	}
	

	SDL_RenderPresent(Game::gRenderer);


	
}

void CPlayState::Cleanup()
{
	SDL_DestroyTexture(bg);

	Mix_FreeMusic(bgm);
	

	newPlayer.getComponent<SpriteComponent>().freeTxt();
	newPlayer.getComponent<Stats>().~Stats();


	for (auto& e : enemies)
	{
		if (e->isActive())
		{
			e->destroy();
		}
	}






	printf("CPlayState Cleanup\n");
}



