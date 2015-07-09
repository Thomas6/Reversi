#include "ReversiModel.h"
#include <vector>

ReversiModel::ReversiModel(Board board, Player player)
{
	board_ = board;
	player_ = BLACK_PLAYER;
}

void ReversiModel::setCurrentPlayer(Player player)
{
	player_ = player;
}

// use a blob finder algorithm? Should be faster. use a growing vector of possible moves/empty spaces rather than searching the board over and over.
BoardSquare* getMoves(Board board, Player player, bool returnValidMoves)
{
	// find all non empty board squares
	std::vector<BoardSquare> nonEmptyBoardSquares;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (board.getBoardSquare(i, j).getState() != EMPTY)
			{
				nonEmptyBoardSquares.push_back(board.getBoardSquare(i, j));
			}
		}
	}

	// now, find all adjacent squares to those that are empty.
	BoardSquare currentSquare;
	int currentSquareRow;
	int currentSquareColumn;
	std::vector<BoardSquare> adjacentEmptySquares;
	while (!nonEmptyBoardSquares.empty())
	{
		currentSquare = nonEmptyBoardSquares.back();
		currentSquareRow = currentSquare.getRow();
		currentSquareColumn = currentSquare.getColumn();
		
		getAdjacentEmptySquares(board, currentSquareRow, currentSquareColumn);

		//if(board.getBoardSquare(
		nonEmptyBoardSquares.pop_back();
	}
}

std::vector<BoardSquare> getAdjacentEmptySquares(Board board, int currentSquareRow, int currentSquareColumn)
{
	// check all 8 adjacent squares to the current squares and return the empty ones
}