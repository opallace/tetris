#ifndef _IO_
#define _IO_

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class IO
{
  public:
    IO                      ();

    void DrawRectangle      (int pX1, int pY1, int pX2, int pY2, int color[]);
    void ClearScreen        ();
    int GetScreenHeight     ();
    int InitGraph           ();
    int Pollkey             ();
    void UpdateScreen       ();
};

#endif
