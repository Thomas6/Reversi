#ifndef BOARDSQUARE_H 
#define BOARDSQUARE_H

enum State { EMPTY, WHITE, BLACK, OFFBOARD };

class BoardSquare
{
	int row_;
	int column_;
	State state_;

    public:
		BoardSquare();
		BoardSquare(int row, int column, State state);

		int getRow();
		int getColumn();
		State getState();
		void setState(State state);
};

#endif // BOARDSQUARE_H // end