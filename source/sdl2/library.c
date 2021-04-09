/*
Copyright 2021 Gameblabla

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "library.h"

static SDL_Window* game_screen;
static SDL_Renderer* renderer;

static Mix_Music* mus;

#define FPS_VIDEO 60
const float real_FPS = 1000/FPS_VIDEO;

SDL_Texture* Load_Image_game(const char* str)
{
	SDL_Texture *texture_tmp;
	SDL_Surface *tmp;
	
	tmp = SDL_LoadBMP(str);
	if (!tmp)
	{
		printf("Could not load image file, exit now\n");
		return NULL;	
	}
	
	texture_tmp = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	
	return texture_tmp;
}

void Display_image(Image_data* texture_tmp, int x, int y)
{
	SDL_Rect rct;
	int w, h;
	SDL_QueryTexture(texture_tmp, NULL, NULL, &w, &h);
		
	rct.x = x;
	rct.y = y;
	rct.w = w;
	rct.h = h;

	SDL_RenderCopy(renderer, texture_tmp, NULL, &rct);
}

int Init_Video(int w, int h)
{
	int flag;
	int width, height;
	SDL_Init( SDL_INIT_VIDEO );
	game_screen = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	if (!game_screen)
	{
		printf("SDL_Init failed Window: %s\n", SDL_GetError());
		return 0;
	}
	
	if (!SDL_GL_SetSwapInterval(-1))
	{
		printf("Freesync not supported or enabled. Renabling Lock FPS again for that reason.\n");
		flag = SDL_RENDERER_PRESENTVSYNC;
	}
	
	/* Create renderer, its resolution, set to HARDWARE aceleration and Vsync turned on */
	renderer = SDL_CreateRenderer(game_screen, -1, SDL_RENDERER_ACCELERATED | flag);
	SDL_RenderSetLogicalSize(renderer, w, h);
	
	/* Clear everything on screen */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	/* Hide the mouse and grab it */
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	SDL_GetWindowSize(game_screen, &width, &height);
	printf("Video OK ! Width %d, Heigth %d\n", width, height);
	
	return 1;
}

void Flip_video(void)
{
	Uint32 start;
	start = SDL_GetTicks();
	SDL_RenderPresent(renderer);
	if(real_FPS > SDL_GetTicks()-start) SDL_Delay(real_FPS-(SDL_GetTicks()-start));
}

void Unload_Image(Image_data* img)
{
	if (img)
	{
		SDL_DestroyTexture(img);
		img = NULL;
	}
}

void Quit_video(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(game_screen);
	SDL_Quit();	
}



int Init_Audio()
{
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
	Mix_AllocateChannels(32);
	return 1;
}

void Load_Music(const char* directory)
{
	if (mus)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(mus);	
	}
	mus = Mix_LoadMUS(directory);
}

void Play_Music(uint8_t loop)
{
	if (loop == 1) 	Mix_PlayMusic(mus, -1);
	else Mix_PlayMusic(mus, 0);
}

void Play_Snd(Sound_data* chk)
{
	Mix_PlayChannel(-1, chk, 0) ;
}

Sound_data* Load_SFX(const char* directory)
{
	return Mix_LoadWAV(directory);
}

void Unload_SFX(Sound_data* chk)
{
	Mix_FreeChunk(chk);
	chk = NULL;
}

void Unload_music()
{
	Mix_HaltMusic();
	Mix_FreeMusic(mus);	
}
