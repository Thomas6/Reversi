#ifndef TURN_H 
#define TURN_H

#include "BoardSquare.h"

enum Direction_Name { LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT };

struct Direction
{
    Direction_Name dir_name;
	int row_offset;
	int col_offset;
};

// will change this later, but its fine for now
struct ValidMove
{
	int row;
	int col;
	Direction_Name* p_dirs;
	int p_dirs_size;
};

class Turn
{
	ValidMove* p_vm_array_;
	//int p_vm_array_size_;
	State pc_;
    public:
		//
		Turn();

		//
		Turn(ValidMove* p_vm, State pc);

		//
		//int getValidMoveArraySize();

		//
		ValidMove* getValidMoves();

		//
		State getPlayerColour();
};

#endif // TURN_H // end