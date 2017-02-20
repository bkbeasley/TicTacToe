#ifndef CSURFACE_HPP_INCLUDED
#define CSURFACE_HPP_INCLUDED

#include <SDL/SDL.h>
#include <string>

class CSurface
{
    public:
       static SDL_Surface* OnLoad(std::string File);

       static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

       static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);

    public:
       CSurface();
};

#endif // CSURFACE_HPP_INCLUDED
