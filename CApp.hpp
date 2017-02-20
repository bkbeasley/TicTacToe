#ifndef CAPP_HPP_INCLUDED
#define CAPP_HPP_INCLUDED

#include <SDL/SDL.h>
#include "CSurface.hpp"  //
#include "CEvent.hpp"


class CApp : public CEvent
{
    private:
       bool             running;

       SDL_Surface*     Surf_Screen;
       SDL_Surface*     Surf_Grid;
       SDL_Surface*     Surf_X;
       SDL_Surface*     Surf_O;
       SDL_Surface*     Surf_StrikeAcross;
       SDL_Surface*     Surf_StrikeDown;
       SDL_Surface*     Surf_StrikeDiagBack;
       SDL_Surface*     Surf_StrikeDiagFwd;
       SDL_Surface*     Surf_XWins;
       SDL_Surface*     Surf_OWins;

    private:
        int             Grid[9];
        int             CurrentPlayer;
        enum            {GRID_TYPE_NONE, GRID_TYPE_X, GRID_TYPE_O};
        bool            GameReset;

    public:
       bool OnInit();
       int  OnExecute();
       void OnEvent(SDL_Event* Event);
       void OnLButtonDown(int mX, int mY);
       void OnExit();
       void OnLoop();
       void OnRender();
       void OnCleanup();

    public:
        void Reset();
        void SetCell(int ID, int Type);
        bool PlayerWins();
        bool ScreenReset();

    public:
        CApp();
};

#endif // CAPP_HPP_INCLUDED
