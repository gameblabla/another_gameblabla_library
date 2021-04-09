#include <stdio.h>
#include <stdlib.h>

#include "library.h"

Image_data *tex;

int main (int argc, char *argv[]) 
{
	SDL_Event event;
	int quit = 0;
	
	const char ut[] = u8"This is a unicode string : ééé";
	printf("%s \n", ut);

	if (!Init_Video(320, 240))
	{
		printf("Failed to create window, exit\n");
		return 0;
	}
	
	tex = Load_Image_game("assets/image.bmp");
	
	while(!quit)
	{

		while (SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDL_KEYUP:
					switch(event.key.keysym.sym) 
					{
						case SDLK_HOME:
						case SDLK_3:
						case SDLK_RCTRL:
						case SDLK_ESCAPE:
							quit = 1;
						break;
						default:
						break;
					}
				break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) 
					{
						case SDLK_LCTRL:
						break;
						default:
						break;
					}
				break;
				case SDL_QUIT:
					quit = 1;
				break;
			}
		}


		Display_image(tex, 50, 50);
		Flip_video();
	}
	
	Unload_Image(tex);
	Quit_video();
}
