#ifndef REVERSIMODEL_H 
#define REVERSIMODEL_H

#include "Board.h"
#include "PlayerTurn.h"

enum Player { BLACK_PLAYER, WHITE_PLAYER };

class ReversiModel
{
	Board board_;
	Player player_;
    public:

		// initialize the board and the starting player
		ReversiModel(Board board, Player player);

		//
		void setCurrentPlayer(Player player);

		// what are the valid moves that a player can make on their turn?
		BoardSquare* getValidMoves(Board board, Player player);
        
		//
		void resolveMove(Board &board, BoardSquare boardSquare);

		//
		bool isGameOver();

		//
		int getScore(Board board);

};

#endif // REVERSIMODEL_H