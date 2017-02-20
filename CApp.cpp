/*
A simple Tic-Tac-Toe game. Players take turns marking a box in
the grid with an X or O. The first player to get 3-in-a-row
wins.
*/

#include "CApp.hpp"



CApp::CApp()     //Default Constructor for the main application
{
    CurrentPlayer = 0;

    Surf_Screen = NULL;
    Surf_Grid   = NULL;
    Surf_X      = NULL;
    Surf_O      = NULL;
    Surf_StrikeAcross = NULL;
    Surf_StrikeDown   = NULL;
    Surf_StrikeDiagBack = NULL;
    Surf_StrikeDiagFwd  = NULL;
    Surf_XWins  = NULL;
    Surf_OWins  = NULL;

    running     = true;
    GameReset   = false;

}


bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    SDL_WM_SetCaption("Tic-Tac-Toe", NULL);

    if((Surf_Screen = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    if((Surf_Grid = CSurface::OnLoad("./gfx/grid.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_X = CSurface::OnLoad("./gfx/x.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_O = CSurface::OnLoad("./gfx/o.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_StrikeAcross = CSurface::OnLoad("./gfx/strike_across.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_StrikeDown = CSurface::OnLoad("./gfx/strike_down.bmp"))== NULL)
    {
        return false;
    }

    if((Surf_StrikeDiagBack = CSurface::OnLoad("./gfx/strike_diagback.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_StrikeDiagFwd = CSurface::OnLoad("./gfx/strike_diagfwd.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_XWins = CSurface::OnLoad("./gfx/x_wins.bmp")) == NULL)
    {
        return false;
    }

    if((Surf_OWins = CSurface::OnLoad("./gfx/o_wins.bmp")) == NULL)
    {
        return false;
    }

    CSurface::Transparent(Surf_X, 255, 0, 255);
    CSurface::Transparent(Surf_O, 255, 0, 255);
    CSurface::Transparent(Surf_StrikeAcross, 255, 255, 255);
    CSurface::Transparent(Surf_StrikeDown, 255, 255, 255);
    CSurface::Transparent(Surf_StrikeDiagBack, 255, 255, 255);
    CSurface::Transparent(Surf_StrikeDiagFwd, 255, 255, 255);


    Reset();

    return true;

}


int CApp::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }


    SDL_Event Event;

    while(running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
        while(ScreenReset())
        {
            OnRender();
            Reset();
        }

    }

    OnCleanup();

    return 0;
}


void CApp::OnEvent(SDL_Event* Event)
{
     CEvent::OnEvent(Event);
}


void CApp::OnLButtonDown(int mX, int mY)
{
    int ID  = mX/200;
        ID += ((mY/200) * 3);

    if(Grid[ID] != GRID_TYPE_NONE)
    {
        return;
    }

    if(CurrentPlayer == 0)
    {
        SetCell(ID, GRID_TYPE_X);
        CurrentPlayer = 1;
    }
    else
    {
        SetCell(ID, GRID_TYPE_O);
        CurrentPlayer = 0;
    }

}


void CApp::OnLoop()
{
}


void CApp::OnRender()
{
     CSurface::OnDraw(Surf_Screen, Surf_Grid, 0, 0);

     for(int i = 0; i < 9; i++)
     {
         int X = (i%3) * 200;
         int Y = (i/3) * 200;

         if(Grid[i] == GRID_TYPE_X)
         {
             CSurface::OnDraw(Surf_Screen, Surf_X, X, Y);
         }

         else if(Grid[i] == GRID_TYPE_O)
         {
             CSurface::OnDraw(Surf_Screen, Surf_O, X, Y);
         }

      }

     if(PlayerWins() == true)
     {
        if(Grid[0] == GRID_TYPE_X && Grid[1] == GRID_TYPE_X && Grid[2] == GRID_TYPE_X)
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeAcross, 0, 0);
           CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[0] == GRID_TYPE_O && Grid[1] == GRID_TYPE_O && Grid[2] == GRID_TYPE_O)  //row 1 across
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeAcross, 0, 0);
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
        else if(Grid[3] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[5] == GRID_TYPE_X)
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeAcross, 0, 200);
           CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[3] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[5] == GRID_TYPE_O)    //row 2 across
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeAcross, 0, 200);
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
        else if(Grid[6] == GRID_TYPE_X && Grid[7] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeAcross, 0, 400);
           CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[6] == GRID_TYPE_O && Grid[7] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)  //row 3 across
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeAcross, 0, 400);
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
        else if(Grid[0] == GRID_TYPE_X && Grid[3] == GRID_TYPE_X && Grid[6] == GRID_TYPE_X)
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeDown, 0, 0);
           CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[0] == GRID_TYPE_O && Grid[3] == GRID_TYPE_O && Grid[6] == GRID_TYPE_O)   //column 1 down
        {
           CSurface::OnDraw(Surf_Screen, Surf_StrikeDown, 0, 0);
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
        else if(Grid[1] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[7] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDown, 200, 0);
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[1] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[7] == GRID_TYPE_O)   //column 2 down
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDown, 200, 0);
            CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
        else if(Grid[2] == GRID_TYPE_X && Grid[5] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDown, 400, 0);
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[2] == GRID_TYPE_O && Grid[5] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)   //column 3 down
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDown, 400, 0);
            CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
         else if(Grid[0] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDiagBack, 0, 0);
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[0] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)   //diagonal back
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDiagBack, 0, 0);
            CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }
        else if(Grid[2] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[6] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDiagFwd, 0, 0);
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        }
        else if(Grid[2] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[6] == GRID_TYPE_O)   //diagonal forward
        {
            CSurface::OnDraw(Surf_Screen, Surf_StrikeDiagFwd, 0, 0);
            CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        }

     }

     SDL_Flip(Surf_Screen);

}


void CApp::OnExit()
{
    running = false;
}



void CApp::OnCleanup()
{
    SDL_FreeSurface(Surf_Screen);
    SDL_FreeSurface(Surf_Grid);
    SDL_FreeSurface(Surf_X);
    SDL_FreeSurface(Surf_O);
    SDL_FreeSurface(Surf_StrikeAcross);
    SDL_FreeSurface(Surf_StrikeDown);
    SDL_FreeSurface(Surf_StrikeDiagBack);
    SDL_FreeSurface(Surf_StrikeDiagFwd);
    SDL_FreeSurface(Surf_XWins);

    SDL_Quit();
}


void CApp::Reset()
{
    for(int i = 0; i < 9; i++)
    {
        Grid[i] = GRID_TYPE_NONE;
    }

}


void CApp::SetCell(int ID, int Type)
{
    if(ID < 0 || ID >= 9)
    {
        return;
    }

    if(Type < 0 || Type > GRID_TYPE_O)
    {
        return;
    }

    Grid[ID] = Type;
}

bool CApp::PlayerWins()
{
    bool winFlag;

    if(Grid[0] == GRID_TYPE_X && Grid[1] == GRID_TYPE_X && Grid[2] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[0] == GRID_TYPE_O && Grid[1] == GRID_TYPE_O && Grid[2] == GRID_TYPE_O)  //row 1 across
    {
        winFlag = true;
    }
    else if(Grid[3] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[5] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[3] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[5] == GRID_TYPE_O)    //row 2 across
    {
        winFlag = true;
    }
    else if(Grid[6] == GRID_TYPE_X && Grid[7] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[6] == GRID_TYPE_O && Grid[7] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)  //row 3 across
    {
        winFlag = true;
    }
    else if(Grid[0] == GRID_TYPE_X && Grid[3] == GRID_TYPE_X && Grid[6] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[0] == GRID_TYPE_O && Grid[3] == GRID_TYPE_O && Grid[6] == GRID_TYPE_O)   //column 1 down
    {
        winFlag = true;
    }
    else if(Grid[1] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[7] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[1] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[7] == GRID_TYPE_O)   //column 2 down
    {
        winFlag = true;
    }
    else if(Grid[2] == GRID_TYPE_X && Grid[5] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[2] == GRID_TYPE_O && Grid[5] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)   //column 3 down
    {
        winFlag = true;
    }
    else if(Grid[0] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[0] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)   //diagonal back
    {
        winFlag = true;
    }
    else if(Grid[2] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[6] == GRID_TYPE_X)
    {
        winFlag = true;
    }
    else if(Grid[2] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[6] == GRID_TYPE_O)   //diagonal forward
    {
        winFlag = true;
    }


    return winFlag;
}


bool CApp::ScreenReset()
{
    if(Grid[0] == GRID_TYPE_X && Grid[1] == GRID_TYPE_X && Grid[2] == GRID_TYPE_X)
    {
        CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
    }
     else if(Grid[0] == GRID_TYPE_O && Grid[1] == GRID_TYPE_O && Grid[2] == GRID_TYPE_O)  //row 1 across
        {
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[3] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[5] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
            SDL_Delay(600);
            return true;
        }
        else if(Grid[3] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[5] == GRID_TYPE_O)    //row 2 across
        {
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[6] == GRID_TYPE_X && Grid[7] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
        {
           CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[6] == GRID_TYPE_O && Grid[7] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)  //row 3 across
        {
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[0] == GRID_TYPE_X && Grid[3] == GRID_TYPE_X && Grid[6] == GRID_TYPE_X)
        {
           CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[0] == GRID_TYPE_O && Grid[3] == GRID_TYPE_O && Grid[6] == GRID_TYPE_O)   //column 1 down
        {
          CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[1] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[7] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[1] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[7] == GRID_TYPE_O)   //column 2 down
        {
            CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[2] == GRID_TYPE_X && Grid[5] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[2] == GRID_TYPE_O && Grid[5] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)   //column 3 down
        {
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
         else if(Grid[0] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[8] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[0] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[8] == GRID_TYPE_O)   //diagonal back
        {
           CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[2] == GRID_TYPE_X && Grid[4] == GRID_TYPE_X && Grid[6] == GRID_TYPE_X)
        {
            CSurface::OnDraw(Surf_Screen, Surf_XWins, 0, 0);
        SDL_Delay(600);
        return true;
        }
        else if(Grid[2] == GRID_TYPE_O && Grid[4] == GRID_TYPE_O && Grid[6] == GRID_TYPE_O)   //diagonal forward
        {
            CSurface::OnDraw(Surf_Screen, Surf_OWins, 0, 0);
        SDL_Delay(600);
        return true;
        }

    return false;
}


int main(int argc, char* argv[])
{
    CApp mainApp;

   return mainApp.OnExecute();

}
