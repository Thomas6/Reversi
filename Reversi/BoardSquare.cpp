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

/*
bool operator == (const BoardSquare &L, const BoardSquare &R)
{
	BoardSquare R_bs = R;
	BoardSquare L_bs = L;
    return(R_bs.getRow() == L_bs.getRow() && R_bs.getCol() == L_bs.getCol());
}
*/
