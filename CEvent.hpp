#ifndef CEVENT_HPP_INCLUDED
#define CEVENT_HPP_INCLUDED

#include <SDL/SDL.h>


class CEvent
{
    public:
       CEvent();

    public:
       virtual void OnEvent(SDL_Event* Event);
       virtual void OnLButtonDown(int mX, int mY);
       virtual void OnExit();
       virtual void OnMouseFocus();
       virtual void OnMouseBlur();
       virtual void OnInputFocus();
       virtual void OnInputBlur();
       virtual void OnRestore();
       virtual void OnMinimize();
};


#endif // CEVENT_HPP_INCLUDED
