#include "BoardSquare.h"

BoardSquare::BoardSquare()
{
	row_ = 0;
	col_ = 0;
	state_ = EMPTY;
}

BoardSquare::BoardSquare(int row, int col, State state)
{
	row_ = row;
	col_ = col;
	state_ = state;
}

int BoardSquare::getRow()
{
	return row_;
}

int BoardSquare::getCol()
{
	return col_;
}

State BoardSquare::getState()
{
	return state_;
}

void BoardSquare::setState(State state)
{
	state_ = state;
}
