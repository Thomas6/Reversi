#include "CppInterfaces.h"

#include "Board.h"

Board::Board()
{
	// construct all the boardsquares on the board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bs_matrix_[i][j] = BoardSquare(i+1, j+1, EMPTY);
		}
	}
	
	// set the center 4 board spaces to their proper starting state
	setBoardSquareState(getBoardSquare(4,4), WHITE);
	setBoardSquareState(getBoardSquare(4,5), BLACK);
	setBoardSquareState(getBoardSquare(5,4), BLACK);
	setBoardSquareState(getBoardSquare(5,5), WHITE);
	
	// this will be used to represent a board square thats off the edge of the board
	offboard_bs_= BoardSquare(-1, -1, OFFBOARD);
}

BoardSquare* Board::getBoardSquare(int row, int col)
{
	// check to see if row and column are valid
	if (row > 8 || row < 1 || col > 8 || col < 1)
	{
		// if not, return board_square_offboard_
		return &offboard_bs_;
	}
	return &bs_matrix_[row-1][col-1];
}

void Board::setBoardSquareState(BoardSquare* p_bs, State state)
{
	p_bs->setState(state);
}