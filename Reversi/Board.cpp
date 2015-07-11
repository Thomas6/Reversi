#include "Board.h"

Board::Board()
{
	pp_board_square_matrix_ = new BoardSquare*[8];
	for (int i = 0; i < 8; i++)
	{
		pp_board_square_matrix_[i] = new BoardSquare[8];
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pp_board_square_matrix_[i][j] = BoardSquare(i+1, j+1, EMPTY);
		}
	}

	// set the center 4 board spaces to their proper starting state
	setBoardSquareState(getBoardSquare(4,4), WHITE);
	setBoardSquareState(getBoardSquare(4,5), BLACK);
	setBoardSquareState(getBoardSquare(5,4), BLACK);
	setBoardSquareState(getBoardSquare(5,5), WHITE);

	BoardSquare* boardsquare = getBoardSquare(5,5);

	// this will be used to represent a board square thats off the edge of the board
	board_square_offboard_ = BoardSquare(-1, -1, OFFBOARD);
}

BoardSquare* Board::getBoardSquare(int row, int column)
{
	// check to see if row and column are valid
	if (row > 8 || row < 1 && column > 8 && column < 1)
	{
		// if not, return board_square_offboard_
		return &board_square_offboard_;
	}
	return &pp_board_square_matrix_[row-1][column-1];
}

void Board::setBoardSquareState(BoardSquare* p_boardSquare, State state)
{
	p_boardSquare->setState(state);
}