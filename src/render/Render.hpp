#ifndef __MANGO_RENDER_HPP__
#define __MANGO_RENDER_HPP__

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>

namespace mango
{

TTF_Font* LoadFont(const char *path,int ptsize);

}

#endif
