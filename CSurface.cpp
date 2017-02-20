#include "CSurface.hpp"

CSurface::CSurface()
{
}

SDL_Surface* CSurface::OnLoad(std::string File)
{
    SDL_Surface* Surf_Temp     = NULL;
    SDL_Surface* Surf_Return   = NULL;

    if((Surf_Temp = SDL_LoadBMP(File.c_str())) == NULL)
    {
        return NULL;
    }

    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}



bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
{
     if(Surf_Dest == NULL || Surf_Src == NULL)
     {
         return false;
     }

     SDL_Rect DestR;

     DestR.x = X;
     DestR.y = Y;

     SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

     return true;
}


bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B)
{
     if(Surf_Dest == NULL)
     {
         return false;
     }

     SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));

     return true;
}
