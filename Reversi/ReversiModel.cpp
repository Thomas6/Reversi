#include "ReversiModel.h"


ReversiModel::ReversiModel(Board board)
{
	board_ = board;

	playerColour_ = BLACK;

	// the initial board configuration
	nonEmptyBoardSquares_.push_back(BoardSquare(4, 4, BLACK));
	nonEmptyBoardSquares_.push_back(BoardSquare(4, 5, WHITE));
	nonEmptyBoardSquares_.push_back(BoardSquare(5, 4, WHITE));
	nonEmptyBoardSquares_.push_back(BoardSquare(5, 5, BLACK));

	// the initial empty boardsquares adjacent to the starting pieces
	adjacentEmptyBoardSquares_.push_back(BoardSquare(3, 3, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(3, 4, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(3, 5, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(3, 6, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(4, 6, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(5, 6, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(6, 6, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(6, 5, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(6, 4, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(6, 3, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(5, 3, EMPTY));
	adjacentEmptyBoardSquares_.push_back(BoardSquare(4, 3, EMPTY));
}

void setValidMove(int row, int column, Direction* dirs, ValidMove* validMove)
{
	validMove->row = row;
	validMove->column = column;
	validMove->dirs = dirs;
}

void ReversiModel::setCurrentPlayer(State playerColour)
{
	playerColour_ = playerColour;
}

// use a blob finder algorithm? Should be faster. use a growing vector of possible moves/empty spaces rather than searching the board over and over.
ValidMove* getValidMoves(Board board, State playerColour, bool returnValidMoves, std::vector<BoardSquare> nonEmptyBoardSquares, std::vector<BoardSquare> adjacentEmptyBoardSquares)
{
	BoardSquare currentEmptyBoardSquare;
	while (!adjacentEmptyBoardSquares.empty())
	{
	    currentEmptyBoardSquare = adjacentEmptyBoardSquares.back();
		if (returnValidMoves == true)
		{
			//getValidMoves();
		}
		else
		{
			//getInvalidMoves();
		}
	}
	// make the compiler error go away
	ValidMove* validMove = new ValidMove;
	return validMove;
}

/*
std::vector<BoardSquare> getAdjacentEmptySquares(Board board, int currentSquareRow, int currentSquareColumn)
{
	// check all 8 adjacent squares to the current squares and return the empty ones
}
*/

int getOtherPlayerColor(State playerColour)
{
	if(playerColour == BLACK)
	{
		return WHITE;
	}
	else // playerColour is white
	{
		return BLACK;
	}
}

bool checkDirection(BoardSquare currentEmptyBoardSquare, Board board, State playerColour, int rowOffset, int columnOffset)
{
	BoardSquare examinedBoardSquare;

	examinedBoardSquare = board.getBoardSquare(currentEmptyBoardSquare.getRow() + rowOffset, currentEmptyBoardSquare.getColumn() + columnOffset);
	// if the board square being examined is of the other player's colour, then there is the potential for a move in this direction
	if (examinedBoardSquare.getState() == getOtherPlayerColor(playerColour))
	{
		// now we check the board square beyond this one to see if it is a valid move 
		examinedBoardSquare = board.getBoardSquare(examinedBoardSquare.getRow() + rowOffset, examinedBoardSquare.getColumn() + columnOffset);
		// if it is of the current player's colour, then this is definitely a valid move
		if (examinedBoardSquare.getState() == playerColour)
		{
			return true;
		}
		// if it is yet another board square of the other player's colour...
		else if (examinedBoardSquare.getState() == getOtherPlayerColor(playerColour))
		{
			// ...we must keep on going until we find a board square that is either of our colour or something else
			while(examinedBoardSquare.getState() == getOtherPlayerColor(playerColour))
			{
				examinedBoardSquare = board.getBoardSquare(examinedBoardSquare.getRow() + rowOffset, examinedBoardSquare.getColumn() + columnOffset);
				// if we found a board square that is of the current player's colour, then this is definitely a valid move
				if (examinedBoardSquare.getState() == playerColour)
				{
					return true;
		        }
				// if we found a board square that is either empty or off board, then we go on to the next direction
				else if (examinedBoardSquare.getState() == EMPTY || OFFBOARD)
				{
					return false;
				}
			}
		}
		// if its not either player colour, then the examined board square is empty or off board, and we must look in a different direction
		else
		{
			 return false;
		}
	}
	// if the board square being examined is not of the other player's colour, then we go on to the next direction
	else
	{
		return false;
	}
}

ValidMove* getValidMove(BoardSquare currentEmptyBoardSquare, Board board, State playerColour)
{
	// store the directions for a valid move somewhere while we determine the capture line directions
	int tempDirs[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	// check left
	if(checkDirection(currentEmptyBoardSquare, board, playerColour, 0, -1))
	{
		//return true;
		tempDirs[0] = LEFT;
	}
	// check up left
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, -1, -1))
	{
		//return true;
		tempDirs[1] = UP_LEFT;
	}
	// check up
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, -1, 0))
	{
		//return true;
		tempDirs[2] = UP;
	}
	// check up right
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, -1, 1))
	{
		//return true;
		tempDirs[3] = UP_RIGHT;
	}
	// check right
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, 0, 1))
	{
		//return true;
		tempDirs[4] = RIGHT;
	}
	// check down right
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, 1, 1))
	{
		//return true;
		tempDirs[5] = DOWN_RIGHT;
	}
	// check down
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, 1, 0))
	{
		//return true;
		tempDirs[6] = DOWN;
	}
	// check down left
	else if (checkDirection(currentEmptyBoardSquare, board, playerColour, 1, -1))
	{
		//return true;
		tempDirs[7] = DOWN_LEFT;
	}
	else
	{
	    return NULL;
	}

	// find the number of directions for possible line captures for the valid move
	int numDirs = 0;
	for (int i = 0; i < 8; i++)
	{
		if (tempDirs[i] != -1)
		{
			numDirs++;
		}
	}
	Direction* dirs = new Direction[numDirs];
	// assign the line captures to di
	int j = 0;
	for (int i = 0; i < 8; i++)
	{
		if (tempDirs[i] != -1)
		{
			dirs[j] = (Direction)tempDirs[i];
			j++;
		}
	}
	ValidMove* p_validMove = new ValidMove;
	setValidMove(currentEmptyBoardSquare.getRow(), currentEmptyBoardSquare.getColumn(), dirs, p_validMove);
	return p_validMove;
}


