#ifndef _BOARD_
#define _BOARD_

#include "Pieces.h"

#define BOARD_LINE_WIDTH 16
#define BLOCK_SIZE 24
#define BOARD_POSITION 320
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define PIECE_BLOCKS 5

class Board
{
  public:
    Board                    (Pieces *pPieces, int pScreenHeight);

    int GetXPosInPixels      (int pPos);
    int GetYPosInPixels      (int pPos);
    bool IsFreeBlock         (int pX, int pY);
    bool IsPossibleMovement  (int pX, int pY, int pPiece, int pRotation);
    bool IsGameOver          ();
    void StorePiece          (int pX, int pY, int pPiece, int pRotation);
    void DeletePossibleLines ();

    int mLinesCleared = 0;
    int mPiecesStored = 0;
    int mScore        = 0;

  private:
    enum {POS_FREE, POS_FILLED};
    int mBoard [BOARD_WIDTH][BOARD_HEIGHT];
    int mScreenHeight;
    Pieces *mPieces;

    void InitBoard  ();
    void DeleteLine (int pY);
};

#endif
