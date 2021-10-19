#include "Game.h"

Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight)
{
    mScreenHeight = pScreenHeight;
  	mBoard        = pBoard;
  	mPieces       = pPieces;
  	mIO           = pIO;
  	InitGame ();
}

int Game::GetRand(int pA, int pB)
{
  return rand() % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
  srand((unsigned int) time(NULL));

  // First Pieces
  mPiece    = GetRand(0,6);
  mRotation = GetRand(0,3);
  mPosX     = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
  mPosY     = mPieces->GetYInitialPosition(mPiece, mRotation);

  // Next Pieces
  mNextPiece    = GetRand(0,6);
  mNextRotation = GetRand(0,3);
  mNextPosX     = BOARD_WIDTH + 2;
  mNextPosY     = 0;

  // Init Level
  mLevel    = 0;
  mWaitTime = INIT_WAIT_TIME;
}

void Game::CreateNewPiece()
{
  mPiece    = mNextPiece;
  mRotation = mNextRotation;
  mPosX     = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
  mPosY     = mPieces->GetYInitialPosition(mPiece, mRotation);

  mNextPiece    = GetRand(0,6);
  mNextRotation = GetRand(0,3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{

  int x, y;
  int mPixelsX = mBoard->GetXPosInPixels(pX);
  int mPixelsY = mBoard->GetYPosInPixels(pY);
  int color[4] {10,214,0,255};

  for(x=0; x < PIECE_BLOCKS; x++){
    for(y=0; y < PIECE_BLOCKS; y++){
      if(mPieces->GetBlockType(pPiece, pRotation, x, y) != 0){
        mIO->DrawRectangle((mPixelsX + x * BLOCK_SIZE), (mPixelsY + y * BLOCK_SIZE), BLOCK_SIZE - 1, BLOCK_SIZE - 1, color);
      };
    }
  }
}

void Game::DrawBoard()
{
  int x, y;
  int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
  int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
  int mY  = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);


  int color[4] = {165,165,165,255};
  mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, 0, BOARD_LINE_WIDTH, mScreenHeight - 1, color);
  mIO->DrawRectangle (mX2, 0, BOARD_LINE_WIDTH, mScreenHeight - 1, color);

  for(x=0; x < BOARD_WIDTH; x++){
    for(y=0; y < BOARD_HEIGHT; y++){
      if(!mBoard->IsFreeBlock(x,y)){
        int color[4] = {255,255,255,255};
        mIO->DrawRectangle (mX1 + (x * BLOCK_SIZE) + 1, (mY + (y * BLOCK_SIZE)), BLOCK_SIZE - 1, BLOCK_SIZE - 1, color);
      }
    }
  }
}

int Game::GetLinesToNextLevel()
{
  return LINES_PER_LEVEL + (LINES_PER_LEVEL * mLevel);
}

void Game::UpdateWaitTime()
{
  if(INIT_WAIT_TIME - (WAIT_TIME_PER_LEVEL * mLevel) >= MAX_WAIT_TIME){
    mWaitTime = INIT_WAIT_TIME - (WAIT_TIME_PER_LEVEL * mLevel);
  }
}

void Game::UpdateLevel()
{
  if(mBoard->mLinesCleared >= GetLinesToNextLevel()){
    mLevel++;
    UpdateWaitTime();
  }
}

void Game::DrawScene()
{
  DrawBoard();
  DrawPiece(mPosX, mPosY, mPiece, mRotation);
  DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);

  UpdateLevel();
}
