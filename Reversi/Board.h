#ifndef BOARD_H 
#define BOARD_H

#include "BoardSquare.h"

class Board
{
	BoardSquare board_square_matrix_[8][8];
	BoardSquare board_square_offboard_;
    public:
		Board();

		BoardSquare getBoardSquare(int row, int column);
		void setBoardSquareState(BoardSquare boardSquare, State state);
};

#endif // BOARD_H 