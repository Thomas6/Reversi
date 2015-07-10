#ifndef TURN_H 
#define TURN_H

#include "BoardSquare.h"

enum Direction { LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT };

struct ValidMove
{
	int row;
	int column;
	Direction* p_dirs;
};

class Turn
{
	ValidMove* p_ValidMoves_;
	State playerColour_;
    public:

		//
		Turn();

		//
		Turn(ValidMove* p_ValidMoves, State playerColour);

		//
		ValidMove* getValidMoves();

		//
		State getPlayerColour();
};

#endif // TURN_H // end