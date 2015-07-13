#ifndef TURN_H 
#define TURN_H

#include "ReversiModel.h"
#include <vector>

enum Direction_Name { LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT };

struct Direction
{
    Direction_Name dir_name;
	int row_offset;
	int col_offset;
};

struct ValidMove
{
	int row;
	int col;
	int dir_name_array_size;
	Direction_Name* p_dir_name_array;
};

class Turn
{
    private:

		//---------------Attributes--------------------------------

		//
		int p_vm_array_size_;

		//
		ValidMove* p_vm_array_;

		//
		State pc_;

		//
		Direction CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[8];

		//--------------Functions-----------------------------------

		//
		ValidMove constructValidMove(BoardSquare current_empty_bs, Board b, State pc);

		//
		void constructDirection(Direction &dir, int row_offset, int col_offset, Direction_Name dir_name);

		//
		void constructCardinalAndOrdinalDirectionArray();

		//
		bool checkDirection(BoardSquare current_empty_bs, Board b, State pc, int row_offset, int col_offset);

    public:

		//
		Turn();

		//
		Turn(State pc, std::vector<BoardSquare> adjacent_empty_bs_vector, Board b);

		//
		int getValidMoveArraySize();

		//
		ValidMove* getValidMoveArray();

		//
		State getPlayerColour();

		//
		State getOtherPlayerColour(State pc);

		//
		Direction* getCardinalAndOrdinalDirectionsArray();
};

#endif // TURN_H // end