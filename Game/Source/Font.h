#ifndef __FONT_H__
#define __FONT_H__

#include "Defs.h"

#include "SDL/include/SDL.h"

class Textures;

class Font
{
public:

    Font(const char* rtpFontFile);

    ~Font();

    SDL_Texture* GetTextureAtlas();
    SDL_Rect GetCharRec(int value);

private:
	
    bool fontLoaded = false;

	SDL_Texture* texture = nullptr;

    int baseSize = 0;
    int charsCount = 0;
    SDL_Rect charsRecs[128];
};

#endif //__FONT_H__