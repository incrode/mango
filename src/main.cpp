#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>



using namespace std;

int main(int ac,char *av[])
{
	(void)ac;
	(void)av;

	// TODO: Add cmd args file opening
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() != 0)
	{
		cout << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}



	SDL_Event e;
	bool running = true;

	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

		}
		SDL_Delay(17);
	}


	SDL_Quit();
	return (EXIT_SUCCESS);
}
