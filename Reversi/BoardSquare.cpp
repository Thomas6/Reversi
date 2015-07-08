#include "BoardSquare.h"

BoardSquare::BoardSquare()
{
	row_ = 0;
	column_ = 0;
	state_ = EMPTY;
}

BoardSquare::BoardSquare(int row, int column, State state)
{
	row_ = row;
	column_ = column;
	state_ = state;
}

int BoardSquare::getRow()
{
	return row_;
}

int BoardSquare::getColumn()
{
	return column_;
}

State BoardSquare::getState()
{
	return state_;
}

void BoardSquare::setState(State state)
{
	state_ = state;
}
