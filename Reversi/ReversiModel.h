#ifndef REVERSIMODEL_H 
#define REVERSIMODEL_H

#include "Board.h"
#include "Turn.h"
#include <vector>
#include <stack>

struct ValidMove;
class Turn;
//

class ReversiModel
{
	Board b_;
	std::vector<BoardSquare> non_empty_bs_vector_;
	std::vector<BoardSquare> adjacent_empty_bs_vector_;
	Turn* p_t_;
	int invalid_move_count_;
	bool game_over_flag_;
	
    public:

		// initialize the board and the starting player
		ReversiModel(Board b);

		//
		Board* getBoardAddr();

		//
		std::vector<BoardSquare>* getNonEmptyBoardSquareVectorAddr();

		//
		std::vector<BoardSquare>* getAdjacentEmptyBoardSquareVectorAddr();

		//
		Turn* getTurnAddr();

		//
		bool isGameOver();

		//
		int* getScore();

		//
		void updateNonEmptyBoardSquareVector(BoardSquare chosen_bs, State pc);

		// change the name of this guy
		void updateAdjacentEmptySquares(BoardSquare bs);

		// this gets called upon Controller notifying the model?
		void resolveMove(BoardSquare chosen_bs);

		// view interacts with this one?
		void updateBoard();

		//
		void updateView();

		//
		void flipBoardSquares(int chosen_bs_row, int chosen_bs_col, State pc, Board* p_b, int row_offset, int col_offset);

		// debugging!
		void outputBoardToConsole();
};

#endif // REVERSIMODEL_H