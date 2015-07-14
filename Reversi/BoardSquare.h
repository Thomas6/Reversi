#ifndef BOARDSQUARE_H 
#define BOARDSQUARE_H

enum State { EMPTY, WHITE, BLACK, OFFBOARD };

class BoardSquare
{
	int row_;
	int col_;
	State state_;

    public:

		/***************BoardSquare**********************************
		* Constructs board square. Default Constructer.
		* Parameters:
		*    None
		* Returns:
		*    a BoardSquare
		*
		*******************************************************************/
		BoardSquare();

		/***************BoardSquare**********************************
		* Sets a given board square. Sets all the attributes with the parameters given.
		* Parameters:
		*    int row: which row its on
		*    int col: which column its on
		*    State state: the state it starts out as
		* Returns:
		*    a BoardSquare
		*
		*******************************************************************/
		BoardSquare(int row, int col, State state);


		/***************getRow*********************************************
		* Returns the row the board square is in.
		* Parameters:
		*    None.
		* Returns:
		*    int
		*
		*******************************************************************/
		int getRow();

		/***************getCol*********************************************
		* Returns the column the board square is in.
		* Parameters:
		*    None.
		* Returns:
		*    int
		*
		*******************************************************************/
		int getCol();

		/***************getState*********************************************
		* Returns the state of the board square
		* Parameters:
		*    None.
		* Returns:
		*    State (which is an enum)
		*
		*******************************************************************/
		State getState();

		/***************getState*********************************************
		* Sets the state of the board square
		* Parameters:
		*    State state: the state it will be set to
		* Returns:
		*    void
		*
		*******************************************************************/
		void setState(State state);
};

#endif // BOARDSQUARE_H // end