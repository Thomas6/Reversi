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
	Board board_;
	std::vector<BoardSquare> nonEmptyBoardSquares_;
	std::vector<BoardSquare> adjacentEmptyBoardSquares_;
	Turn* p_turn_;

    public:

		//
		Board* getBoardAddr();

		//
		Turn* getTurnAddr();

		// initialize the board and the starting player
		ReversiModel(Board board);

		//
		bool isGameOver();

		//
		int getScore(Board board);

		//
		void setValidMove(int row, int column, Direction* dirs, ValidMove* validMove);

		// what are the valid moves that a player can make on their turn?
		ValidMove* getValidMoves(Board board, State playerColour, std::vector<BoardSquare> adjacentEmptyBoardSquares);
        
		//
		State getOtherPlayerColour(State playerColour);

		//
		ValidMove* getValidMove(BoardSquare currentEmptyBoardSquare, Board board, State playerColour);

		//
		bool checkDirection(BoardSquare currentEmptyBoardSquare, Board board, State playerColour, int rowOffset, int columnOffset);

		// this gets called upon Controller notifying the model?
		void resolveMove(Board* board, BoardSquare boardSquare, Turn* p_Turn);

		// view interacts with this one?
		void updateBoard();

		void updateView();

		void flipBoardSquares(int chosenBoardSquareRow, int chosenBoardSquareColumn, State playerColour, Board* board, int rowOffset, int columnOffset);

		void outputBoardToConsole(Board* p_board);
};

#endif // REVERSIMODEL_H