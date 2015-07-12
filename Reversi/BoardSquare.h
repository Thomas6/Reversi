#ifndef BOARDSQUARE_H 
#define BOARDSQUARE_H

enum State { EMPTY, WHITE, BLACK, OFFBOARD };

class BoardSquare
{
	int row_;
	int col_;
	State state_;

    public:
		BoardSquare();
		BoardSquare(int row, int col, State state);

		int getRow();
		int getCol();
		State getState();
		void setState(State state);

		//bool operator == (const BoardSquare &L, const BoardSquare &R) const;
};

#endif // BOARDSQUARE_H // end