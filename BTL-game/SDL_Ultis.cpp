#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include"SDL_Ultis.h"













SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		cout << "Unable to load image " << path << " SDL_image Error: "
		<< IMG_GetError() << endl;
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);


		if (newTexture == NULL)
			cout << "Unable to create texture from " << path << " SDL Error: "
			<< SDL_GetError() << endl;
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
};





