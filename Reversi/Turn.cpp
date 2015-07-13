#include "Turn.h"

Turn::Turn()
{
	pc_ = BLACK;
}

Turn::Turn(State pc, std::vector<BoardSquare> adjacent_empty_bs_vector, Board b)
{
	BoardSquare current_empty_bs;
	std::stack<ValidMove> temp_vm_stack;
	ValidMove vm;
	pc_ = pc;
	constructCardinalAndOrdinalDirectionArray();
	
	while (!adjacent_empty_bs_vector.empty())
	{
	    current_empty_bs = adjacent_empty_bs_vector.back();
		vm = constructValidMove(current_empty_bs, b, pc);
		if (vm.dir_name_array_size != 0)
		{
			temp_vm_stack.push(vm);
		}
		adjacent_empty_bs_vector.pop_back();
	}

	p_vm_array_size_ = temp_vm_stack.size();
	p_vm_array_ = new ValidMove[p_vm_array_size_];

	for (int i = 0; !temp_vm_stack.empty(); i++)
	{
		p_vm_array_[i] = temp_vm_stack.top();
		temp_vm_stack.pop();
	}
}

void Turn::constructDirection(Direction &dir, int row_offset, int col_offset, Direction_Name dir_name)
{
	dir.row_offset = row_offset;
	dir.col_offset = col_offset;
	dir.dir_name = dir_name;
}

void Turn::constructCardinalAndOrdinalDirectionArray()
{
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[0], 0, -1, LEFT);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[1], -1, -1, UP_LEFT);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[2], -1, 0, UP);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[3], -1, 1, UP_RIGHT);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[4], 0, 1, RIGHT);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[5], 1, 1, DOWN_RIGHT);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[6], 1, 0, DOWN);
	constructDirection(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[7], 1, -1, DOWN_LEFT);
}

bool Turn::checkDirection(BoardSquare current_empty_bs, Board b, State pc, int row_offset, int col_offset)
{
	BoardSquare* p_examined_bs;

	p_examined_bs = b.getBoardSquare(current_empty_bs.getRow() + row_offset, current_empty_bs.getCol() + col_offset);
	// if the board square being examined is of the other player's colour, then there is the potential for a move in this direction
	if (p_examined_bs->getState() == getOtherPlayerColour(pc))
	{
		// now we check the board square beyond this one to see if it is a valid move 
		p_examined_bs = b.getBoardSquare(p_examined_bs->getRow() + row_offset, p_examined_bs->getCol() + col_offset);
		// if it is of the current player's colour, then this is definitely a valid move
		if (p_examined_bs->getState() == pc)
		{
			return true;
		}
		// if it is yet another board square of the other player's colour...
		else if (p_examined_bs->getState() == getOtherPlayerColour(pc))
		{
			// ...we must keep on going until we find a board square that is either of our colour or something else
			while(p_examined_bs->getState() == getOtherPlayerColour(pc))
			{
				p_examined_bs = b.getBoardSquare(p_examined_bs->getRow() + row_offset, p_examined_bs->getCol() + col_offset);
				// if we found a board square that is of the current player's colour, then this is definitely a valid move
				if (p_examined_bs->getState() == pc)
				{
					return true;
		        }
				// if we found a board square that is either empty or off board, then we go on to the next direction
				else if (p_examined_bs->getState() == EMPTY || OFFBOARD)
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

ValidMove Turn::constructValidMove(BoardSquare current_empty_bs, Board b, State pc)
{
	// store the directions for a valid move somewhere while we determine the capture line directions
	ValidMove vm;
	int dir_name_array_size = 0;
	Direction_Name* p_dir_name_array;
	std::stack<Direction_Name> dir_name_stack;

	for (int i = 0; i < 8; i++)
	{
		// if there is a capture line in that direction...
		if (checkDirection(current_empty_bs, b, pc, CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[i].row_offset, CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[i].col_offset) == true)
		{
			dir_name_array_size++;
			dir_name_stack.push(CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[i].dir_name);
		}
	}

	// create p_dir_name_array
	p_dir_name_array = new Direction_Name[dir_name_array_size];
	for (int i = 0; !dir_name_stack.empty(); i++)
	{
		p_dir_name_array[i] = dir_name_stack.top();
		dir_name_stack.pop();
	}

	vm.row = current_empty_bs.getRow();
	vm.col = current_empty_bs.getCol();
	vm.dir_name_array_size = dir_name_array_size;
	vm.p_dir_name_array = p_dir_name_array;

	return vm;
}

int Turn::getValidMoveArraySize()
{
	return p_vm_array_size_;
}

ValidMove* Turn::getValidMoveArray()
{
	return p_vm_array_;
}

State Turn::getPlayerColour()
{
	return pc_;
}

State Turn::getOtherPlayerColour(State pc)
{
	if(pc == BLACK)
	{
		return WHITE;
	}
	else // playerColour is white
	{
		return BLACK;
	}
}

Direction* Turn::getCardinalAndOrdinalDirectionsArray()
{
	return CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY;
}
