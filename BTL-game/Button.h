#ifndef BUTTON_H_
#define BUTTON_H_

#include "playState.h"
#include "assets/TextureManager.h"


const int TITLE_BUTTON_WIDTH = 150;
const int TITLE_BUTTON_HEIGHT = 98;



class Button
{
public:
	SDL_Texture* tex;
	int size_x;

	SDL_Rect current_srite_clip;
	SDL_Rect desRect = { 0 , 0 , TITLE_BUTTON_WIDTH , TITLE_BUTTON_HEIGHT};


	

	Button() = default;

	Button(std::string path , int x, int y , int sz);

	void SetPosition(int x, int y);

	void CheckInside(SDL_Event *e );

	void handleEvent(Game* game);

	void Render();

	bool getStatus()
	{
		return inside;
	}

private:


	bool inside = false;
	SDL_Rect mouse_in;
	SDL_Rect mouse_out;
};

#endif // !BUTTON_H_