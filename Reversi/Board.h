#ifndef BOARD_H 
#define BOARD_H

#include "BoardSquare.h"

class Board
{
	// This is what the board is made of. 
	// board_square_matrix_[1][1] represents the top-left corner square;
	// board_square_matrix_[8][8] represents the bottom-right corner square.
	BoardSquare** pp_bs_matrix_;
	// this will be used to represent a board square thats "off the edge" of the board
	BoardSquare offboard_bs_;

    public:

		//
		Board();

		//
		BoardSquare* getBoardSquare(int row, int col);

		//
		void setBoardSquareState(BoardSquare* p_bs, State state);
};

#endif // BOARD_H 