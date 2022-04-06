#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include"SDL_Ultis.h"



SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
        cout << "Unable to load image " << path << " SDL_image Error: "
        << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr)
            cout << "Unable to create texture from " << path << " SDL Error: "
            << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


