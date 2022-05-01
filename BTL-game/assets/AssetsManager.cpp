#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include"../assets/AssetsManager.h"













SDL_Texture* loadTexture(const char* path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		cout << "Unable to load image " << path << " SDL_image Error: "
		<< IMG_GetError() << endl;
	else {
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);


		if (newTexture == NULL)
			cout << "Unable to create texture from " << path << " SDL Error: "
			<< SDL_GetError() << endl;
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
void drawTexture(SDL_Texture* texture, SDL_Rect scr, SDL_Rect des , SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::gRenderer,texture, &scr,& des,NULL,NULL,flip);
	
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





