#include "PlayerTurn.h"

// Black goes first, according to convention
PlayerTurn::PlayerTurn()
{
	turnColor_ = BLACKTURN;
}

PlayerTurn::PlayerTurn(TurnColor turnColor)
{
	turnColor_ = turnColor;
}

