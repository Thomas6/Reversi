#ifndef BOARD_H 
#define BOARD_H

#include "BoardSquare.h"

class Board
{
	// This is what the board is made of. 
	// board_square_matrix_[1][1] represents the top-left corner square;
	// board_square_matrix_[8][8] represents the bottom-right corner square.
	BoardSquare** pp_board_square_matrix_;
	// this will be used to represent a board square thats "off the edge" of the board
	BoardSquare board_square_offboard_;

    public:

		//
		Board();

		//
		BoardSquare* getBoardSquare(int row, int column);

		//
		void setBoardSquareState(BoardSquare* boardSquare, State state);
};

#endif // BOARD_H 