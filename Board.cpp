#include "Board.h"

Board::Board(Pieces *pPieces, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;
	mPieces       = pPieces;
	InitBoard();
}

void Board::InitBoard()
{
  int i,j;
  for(i=0; i < BOARD_WIDTH; i++){
    for(j=0; j < BOARD_HEIGHT; j++){
      mBoard[i][j] = POS_FREE;
    }
  }
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
  int x1, x2, y1, y2;

  for(x1 = pX, x2 = 0; x1 < pX + PIECE_BLOCKS; x1++, x2++){
    for(y1 = pY, y2 = 0; y1 < pY + PIECE_BLOCKS; y1++, y2++){
      if(mPieces->GetBlockType(pPiece, pRotation, x2, y2) != 0){
        mBoard[x1][y1] = POS_FILLED;
				mPiecesStored++;
				// mScore += 50;
      }
    }
  }
}

bool Board::IsGameOver()
{
  int x;
  for(x = 0; x < BOARD_WIDTH; x++){
    if(mBoard[x][0] == POS_FILLED){
      return true;
    }
  }

  return 0;
}

void Board::DeleteLine(int pY)
{
  int x, y;

  for(y = pY; y > 0; y--){
    for(x = 0; x < BOARD_WIDTH; x++){
      mBoard[x][y] = mBoard[x][y-1];
    }
  }
}

void Board::DeletePossibleLines()
{
  int x, y;
	int factor = 1;
  for(y = 0; y < BOARD_HEIGHT; y++){
    x = 0;
    while(x < BOARD_WIDTH){
      if(mBoard[x][y] != POS_FILLED){
        break;
      }
      x++;
    }
    if(x == BOARD_WIDTH){
      DeleteLine(y);
			mLinesCleared++;
			mScore += 100 * factor;
			factor++;
    }
  }
}

bool Board::IsFreeBlock(int pX, int pY)
{
  if(mBoard[pX][pY] == POS_FREE){
    return true;
  }else {
    return 0;
  }
}

int Board::GetXPosInPixels(int pPos)
{
  return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pPos)
{
  return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation)
{
  int x1, x2, y1, y2;

  for(x1 = pX, x2 = 0; x1 < pX + PIECE_BLOCKS; x1++, x2++){
    for(y1 = pY, y2 = 0; y1 < pY + PIECE_BLOCKS; y1++, y2++){
			if (	x1 < 0 || x1 > BOARD_WIDTH  - 1	|| y1 > BOARD_HEIGHT - 1){
				if (mPieces->GetBlockType (pPiece, pRotation, x2, y2) != 0){
					return 0;
				}
			}
			if (y1 >= 0){
				if ((mPieces->GetBlockType (pPiece, pRotation, x2, y2) != 0) &&(!IsFreeBlock(x1, y1))){
					return 0;
				}
			}
    }
  }

  return true;
}
