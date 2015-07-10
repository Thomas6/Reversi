#include "Turn.h"

Turn::Turn()
{
	playerColour_ = BLACK;
	//p_ValidMoves_ = NULL;
}

Turn::Turn(ValidMove* p_ValidMoves, State playerColour)
{
	p_ValidMoves_ = p_ValidMoves;
	playerColour_ = playerColour;
}

ValidMove* Turn::getValidMoves()
{
	return p_ValidMoves_;
}

State Turn::getPlayerColour()
{
	return playerColour_;
}