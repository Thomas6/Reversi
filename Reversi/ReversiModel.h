#ifndef REVERSIMODEL_H 
#define REVERSIMODEL_H

#include "Board.h"
#include <vector>

enum Direction { LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT };

struct ValidMove
{
		int row;
		int column;
		Direction *dirs;
};

class ReversiModel
{
	Board board_;
	State playerColour_;
	std::vector<BoardSquare> nonEmptyBoardSquares_;
	std::vector<BoardSquare> adjacentEmptyBoardSquares_;

    public:

		// initialize the board and the starting player
		ReversiModel(Board board);

		// create a valid move
		void ConstructValidMove(int row, int column, Direction *dirs, ValidMove* validMove);

		//
		void setCurrentPlayer(State playerColour);

		// what are the valid moves that a player can make on their turn?
		ValidMove* getValidMoves(Board board, State playerColour, bool returnValidMoves, std::vector<BoardSquare> nonEmptyBoardSquares, std::vector<BoardSquare> adjacentEmptyBoardSquares);
        
		int getOtherPlayerColor(State playerColour);

		ValidMove* getValidMove(BoardSquare currentEmptyBoardSquare, Board board, State playerColour);

		bool checkDirection(BoardSquare currentEmptyBoardSquare, Board board, State playerColour, int rowOffset, int columnOffset);
		//
		void resolveMove(Board &board, BoardSquare boardSquare);

		//
		bool isGameOver();

		//
		int getScore(Board board);
};

#endif // REVERSIMODEL_H