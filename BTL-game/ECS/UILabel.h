#pragma once

#include"ECS.h"
#include"Components.h"
#include"../assets/AssetsManager.h"

#include"../playState.h"

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>

class UILabel : public Component
{
public:
	UILabel(int xpos , int ypos , std::string text , std::string font, SDL_Color& color)
	:labelText(text) , labelFont(font) , textColor(color)

	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}

	~UILabel() {};

	void SetLabelText(std::string text , std::string font)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(CPlayState::assets->getFont(font), text.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::gRenderer, surf);

		SDL_FreeSurface(surf);

		
		//set wit and heigt;
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}



	void draw() override
	{
		SDL_RenderCopy(Game::gRenderer, labelTexture, nullptr, &position);
		
		SDL_DestroyTexture(labelTexture);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColor;
	SDL_Texture* labelTexture;

};