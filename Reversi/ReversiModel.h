#ifndef REVERSIMODEL_H 
#define REVERSIMODEL_H

#include "Board.h"
#include "Turn.h"
#include <vector>
#include <stack>

struct ValidMove;
class Turn;

class ReversiModel
{
	Board b_;
	std::vector<BoardSquare> non_empty_bs_vector_;
	std::vector<BoardSquare> adjacent_empty_bs_vector_;
	Turn* p_t_;
	bool game_over_flag_;

	//
	bool checkMove(Turn t, int row, int col);

	//
	void updateNonEmptyBoardSquareVector(BoardSquare chosen_bs, State pc);

	// 
	void updateAdjacentEmptySquares(BoardSquare bs);

	// implement game over check when a move is resolved (are there any empty board squares left?)
	void resolveMove(BoardSquare chosen_bs);

	//
	void flipBoardSquares(int chosen_bs_row, int chosen_bs_col, State pc, Board* p_b, int row_offset, int col_offset);

    public:

		//
		ReversiModel();

		// implement this
		State getBoardSquareState(int row, int col);

		// implement this and fater you're done doing that, make a pretty UI for the game. Demonstrate the flexibility to implement whatever UI they damn well feel like.
		bool chooseBoardSquare(int row, int col);

		//
		bool isGameOver();

		//
		int* getScore();

		// debugging!
		void outputBoardToConsole();
};

#endif // REVERSIMODEL_H