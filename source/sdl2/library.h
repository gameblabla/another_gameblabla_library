#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define Image_data SDL_Texture
#define Sound_data Mix_Chunk

extern Image_data* Load_Image_game(const char* str);

extern inline void Display_image(Image_data* texture_tmp, int x, int y);

extern int Init_Video(int w, int h);
extern void Flip_video(void);
extern void Quit_video(void);

extern void Unload_Image(Image_data* img);

extern int Init_Audio();
extern void Load_Music(const char* directory);

extern void Play_Music(uint8_t loop);

extern void Play_Snd(Sound_data* chk);

extern Sound_data* Load_SFX(const char* directory);

extern void Unload_SFX(Sound_data* chk);
extern void Unload_music();

#endif
