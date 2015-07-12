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
	Turn* p_turn_;
	
    public:

		//
		void constructDirection(Direction &dir, int row_offset, int col_offset, Direction_Name dir_name);

		//
		void constructDirectionArray();

		//
		Board* getBoardAddr();

		//
		std::vector<BoardSquare>* getNonEmptyBoardSquareVectorAddr();

		//
		std::vector<BoardSquare>* getAdjacentEmptyBoardSquareVectorAddr();

		//
		Turn* getTurnAddr();

		// initialize the board and the starting player
		ReversiModel(Board b);

		//
		bool isGameOver();

		//
		int getScore(Board b);

		//
		void setValidMove(int row, int col, Direction_Name* p_dirs, int numDirs, ValidMove* p_vm);

		// what are the valid moves that a player can make on their turn?
		ValidMove* getValidMoves(Board b, State pc, std::vector<BoardSquare> adjacent_empty_bs_vector);
        
		//
		State getOtherPlayerColour(State pc);

		//
		ValidMove getValidMove(BoardSquare current_empty_bs, Board b, State pc);

		//
		bool checkDirection(BoardSquare current_empty_bs, Board b, State pc, int row_offset, int col_offset);

		//
		void updateNonEmptyBoardSquareVector(Board* p_b, std::vector<BoardSquare>* p_non_empty_bs_vector, BoardSquare chosen_bs, State pc);

		//
		void getAdjacentEmptySquares(Board b, BoardSquare bs, std::vector<BoardSquare>* p_adjacent_empty_bs_vector);

		// this gets called upon Controller notifying the model?
		void resolveMove(Board* p_b, BoardSquare bs, Turn* p_turn, std::vector<BoardSquare>* p_non_empty_bs_vector, std::vector<BoardSquare>* p_adjacent_empty_bs_vector);

		// view interacts with this one?
		void updateBoard();

		//
		void updateView();

		//
		void flipBoardSquares(int chosen_bs_row, int chosen_bs_col, State pc, Board* p_b, int row_offset, int col_offset);

		//
		void outputBoardToConsole(Board* p_b);
};

#endif // REVERSIMODEL_H