#ifndef BOARD_H 
#define BOARD_H

#include "BoardSquare.h"

//struct BoardSquare

class Board
{
	// This is what the board is made of. 
	// board_square_matrix_[1][1] represents the top-left corner square;
	// board_square_matrix_[8][8] represents the bottom-right corner square.
	BoardSquare bs_matrix_[8][8];

	// this will be used to represent a board square thats "off the edge" of the board
	BoardSquare offboard_bs_;

    public:

		/***************Board**********************************
		* Constructor. This involes setting the initial black and white squares 
		* that you have at the beginning of every Reversi game.
		*
		*******************************************************************/
		Board();


		/***************getBoardSquare**********************************
		* Returns a pointer to a board square. If the coordinates, row and column,
		* point to a location off board, it returns a singular off board square,
		* called offboard_bs_ with a unique state: OFFBOARD
		* Parameters:
		*    int row: number of a row on the board
		*    int col: number of a column on the board
		* Returns:
		*    A pointer to a board square
		*
		*******************************************************************/
		BoardSquare* getBoardSquare(int row, int col);


		/***************setBoardSquareState**********************************
		* Sets the state of a given board square.
		* Parameters:
		*    BoardSquare* p_bs: a pointer to the boardsquare you want to set the state of.
		*    State state: the state you want to set it to.
		* Returns:
		*    void
		*
		*******************************************************************/
		void setBoardSquareState(BoardSquare* p_bs, State state);


};

#endif // BOARD_H 