#ifndef REVERSI_CONTROLLER_H 
#define REVERSI_CONTROLLER_H

#include "ReversiModel.h"
#include <iostream>

class ReversiController
{
	ReversiModel* p_rm_;

    public:

		/***************ReversiController**********************************
		* Initialize reversiModel and control game flow
		* Parameters:
		*   None
		* Returns:
		*   void
		*******************************************************************/
		ReversiController();

		/***************chooseBoardSquare********************************
		* It copies reversiModel's choose board square, but it should be
		* the controller calling that function anyways. This function is called
		* when the player makes a move (ie. chooses a board square)
		* Parameters:
		*    int row: number of a row on the board
		*    int col: number of a column on the board
		* Returns:
		*    bool: returns false if the board square chosen is not a valid move
		*
		*******************************************************************/
		bool chooseBoardSquare(int row, int col);
};

#endif // REVERSI_CONTROLLER_H