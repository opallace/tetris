#include <iostream>
#include "Game.h"

int main()
{

  IO mIO;
  int mScreenHeight = mIO.GetScreenHeight();

  Pieces mPieces;
  Board mBoard(&mPieces, mScreenHeight);
  Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

  unsigned long mTime1 = SDL_GetTicks();

  bool running = true;
  while(running){
    while(mIO.Pollkey() == SDLK_ESCAPE){
      running = false;
    }

    mIO.ClearScreen();
    mGame.DrawScene();
    mIO.UpdateScreen();

    int mKey = mIO.Pollkey();

		switch (mKey)
		{
			case (SDLK_RIGHT):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX++;
					break;
			}
			case (SDLK_LEFT):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;
				break;
			}
			case (SDLK_DOWN):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;
          mBoard.mScore++;
				break;
			}
			case (SDLK_UP):
			{
				    if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					       mGame.mRotation = (mGame.mRotation + 1) % 4;
				break;
			}
      case (SDLK_x):
      {
        while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
          mGame.mPosY++;
          mBoard.mScore++;
        }
        mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);
        mBoard.DeletePossibleLines ();

        if (mBoard.IsGameOver()){
          std::cout << "GAME OVER!!!" << std::endl;
          std::cout << "YOUR SCORE: " << mBoard.mScore << std::endl;
          exit(0);
        }

        mGame.CreateNewPiece();

        break;
      }
		}

		// ----- Vertical movement -----

		unsigned long mTime2 = SDL_GetTicks();

		if((mTime2 - mTime1) > mGame.mWaitTime)
		{
			if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)){
				mGame.mPosY++;
			}else {

          mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
          mBoard.DeletePossibleLines ();

          if (mBoard.IsGameOver()){
            std::cout << "GAME OVER!!!" << std::endl;
            std::cout << "YOUR SCORE: " << mBoard.mScore << std::endl;
            exit(0);
          }
          mGame.CreateNewPiece();

			}
			mTime1 = SDL_GetTicks();

    }
  }

return 0;
}
