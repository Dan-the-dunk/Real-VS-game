#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include"../assets/TextureManager.h"













SDL_Texture* loadTexture(const char* path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		std::cout << "Unable to load image " << path << " SDL_image Error: "
		<< IMG_GetError() << endl;
	else {
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);


		if (newTexture == NULL)
			std::cout << "Unable to create texture from " << path << " SDL Error: "
			<< SDL_GetError() << endl;
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
void drawTexture(SDL_Texture* texture, SDL_Rect scr, SDL_Rect des , SDL_RendererFlip flip )
{
	SDL_RenderCopyEx(Game::gRenderer,texture, &scr,& des,NULL,NULL,flip);
	
}

void drawAngledTexture(SDL_Texture* texture, SDL_Rect scr, SDL_Rect des, SDL_RendererFlip flip, float angle, const SDL_Point* center)
{
	SDL_RenderCopyEx(Game::gRenderer, texture, &scr, &des, angle, center, flip);

}





void bounce_back(Vector2D& vel , bool bounce_right)
{

	vel.x = (bounce_right) ? 2 : -2;
	vel.y = -10;
	
}


void setBlendMode(SDL_BlendMode blending, SDL_Texture** mTexture)
{
	//Set blending function
	SDL_SetTextureBlendMode(*mTexture, blending);
}

void setAlpha(Uint8 alpha, SDL_Texture** mTexture)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(*mTexture, alpha);
}
;



void updateCam(int xpos, int ypos, int mapXmax , int mapYmax)
{
	CPlayState::camera.x = xpos - SCREEN_WIDTH / 2; // gioi han vi tri nhan vat.
	CPlayState::camera.y = ypos - SCREEN_HEIGHT / 2;



	if (CPlayState::camera.x < 0)CPlayState::camera.x = 0;// 0 tac dong gi
	if (CPlayState::camera.x > mapXmax - SCREEN_WIDTH) CPlayState::camera.x = mapXmax - SCREEN_WIDTH;
	if (CPlayState::camera.y < 0) CPlayState::camera.y = 0;// 0 tac dong gi
	if (CPlayState::camera.y > mapYmax - SCREEN_HEIGHT) CPlayState::camera.y = mapYmax - SCREEN_HEIGHT;
}




