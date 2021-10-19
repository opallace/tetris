#include "IO.h"

SDL_Window   *gWindow  = NULL;
SDL_Renderer *renderer = NULL;

void IO::ClearScreen()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

IO::IO()
{
	InitGraph();
}

void IO::DrawRectangle (int pX1, int pY1, int pX2, int pY2, int color[])
{
  SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
  SDL_Rect rect = {pX1, pY1, pX2, pY2};
  SDL_RenderFillRect(renderer, &rect);
}

int IO::GetScreenHeight()
{
  int w, h;
  SDL_GetWindowSize(gWindow, &w, &h);
	return h;
}

void IO::UpdateScreen()
{
	SDL_RenderPresent(renderer);
}

int IO::Pollkey()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) )
	{
		switch (event.type) {
			case SDL_KEYDOWN:
				return event.key.keysym.sym;
			case SDL_QUIT:
				exit(3);
		}
	}
	return -1;
}

int IO::InitGraph()
{

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
    return 1;
  }else{

    gWindow = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if(gWindow == NULL){
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
      return 2;
    }

    renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError());
      return 2;
    }

    return 0;

  }
}
