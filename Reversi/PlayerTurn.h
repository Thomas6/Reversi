#ifndef PLAYERTURN_H 
#define PLAYERTURN_H

#include "ReversiModel.h"

class PlayerTurn
{
    TurnColor turnColor_;

    public:
		enum TurnColor { BLACKTURN, WHITETURN };

		PlayerTurn();
        PlayerTurn(TurnColor turnColor);
};

#endif // PLAYERTURN_H