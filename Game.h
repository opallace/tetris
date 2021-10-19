#ifndef _GAME_
#define _GAME_

#include <ctime>
#include "Board.h"
#include "Pieces.h"
#include "IO.h"

#define INIT_WAIT_TIME      500
#define MAX_WAIT_TIME       50
#define WAIT_TIME_PER_LEVEL 50
#define LINES_PER_LEVEL     10

class Game
{
  public:
    Game (Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

    int mPosX, mPosY;
    int mPiece, mRotation;

    void DrawScene();
    void CreateNewPiece();

    int mLevel;
    int mWaitTime;

  private:
    Board *mBoard;
    Pieces *mPieces;
    IO *mIO;

    int mScreenHeight;
    int mNextPosX, mNextPosY;
    int mNextPiece, mNextRotation;

    int  GetRand(int pA, int pB);
    int  GetLinesToNextLevel();
    void InitGame();
    void DrawPiece(int pX, int pY, int pPiece, int pRotation);
    void DrawBoard();
    void UpdateWaitTime();
    void UpdateLevel();
};

#endif
