#include "Turn.h"

Turn::Turn()
{
	pc_ = BLACK;
	//p_ValidMoves_ = NULL;
}

Turn::Turn(ValidMove* p_vm_array, State pc)
{
	p_vm_array_ = p_vm_array;
	pc_ = pc;
}

/*int getValidMoveArraySize()
{
	//return p_vm_array_size_;
}*/

ValidMove* Turn::getValidMoves()
{
	return p_vm_array_;
}

State Turn::getPlayerColour()
{
	return pc_;
}