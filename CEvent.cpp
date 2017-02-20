#include "CEvent.hpp"

CEvent::CEvent()
{

}

void CEvent::OnEvent(SDL_Event* Event)
{
    switch(Event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            switch(Event->button.button)
            {
                case SDL_BUTTON_LEFT:
                {    OnLButtonDown(Event->button.x, Event->button.y);
                     break;
                }
            }
         }

         case SDL_ACTIVEEVENT:
         {    switch(Event->active.state)
              {
                 case SDL_APPMOUSEFOCUS:
                 {   if(Event->active.gain)
                        OnMouseFocus();
                     else
                        OnMouseBlur();

                     break;
                 }
                 case SDL_APPINPUTFOCUS:
                 {    if(Event->active.gain)
                         OnInputFocus();
                      else
                         OnInputBlur();

                      break;
                 }
                 case SDL_APPACTIVE:
                 {    if(Event->active.gain)
                         OnRestore();
                      else
                         OnMinimize();

                      break;
                 }
              }
              break;
          }

          case SDL_QUIT:
          {    OnExit();
               break;
          }
    }
}


void CEvent::OnLButtonDown(int mX, int mY){
}


void CEvent::OnExit(){
}


void CEvent::OnMouseFocus(){
}


void CEvent::OnMouseBlur(){
}


void CEvent::OnInputFocus(){
}


void CEvent::OnInputBlur(){
}


void CEvent::OnRestore(){
}


void CEvent::OnMinimize(){
}
