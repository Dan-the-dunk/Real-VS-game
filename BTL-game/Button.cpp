#include "Button.h"





Button::Button(string path , int x, int y , int sz)
{


	tex = loadTexture(path.c_str());


	size_x = sz;


	desRect.x = x;
	desRect.y = y;
	desRect.w = size_x;

	mouse_in = { size_x , 0 , size_x , 98 };
	mouse_out = { 0,0 , size_x , 98 };

	current_srite_clip = mouse_out;
}

void Button::SetPosition(int x, int y)
{
	desRect.x = x;
	desRect.y = y;


}

void Button::CheckInside(SDL_Event* e )
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;


		SDL_GetMouseState(&x, &y);


		if ((x > desRect.x) && (x < desRect.x + size_x) && (y > desRect.y) && (y < desRect.y + desRect.h))
		{
			//Set the button sprite
			inside = true;
			current_srite_clip = mouse_in;
		}
		else
		{
			current_srite_clip = mouse_out;
			inside = false;
		}

		

	}
}

void Button::handleEvent(Game* game)
{

	SDL_Event event = CPlayState::ev;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (inside)
		{
			current_srite_clip = mouse_in;
		}

		else
		{
			current_srite_clip = mouse_out;
		}

	}



}
void Button::Render()
{



	if (tex == NULL) cout << "cant load texture " << SDL_GetError() << endl;


	drawTexture(tex, current_srite_clip, desRect, SDL_FLIP_NONE);
}