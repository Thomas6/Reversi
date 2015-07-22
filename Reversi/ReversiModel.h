#ifndef REVERSI_MODEL_H 
#define REVERSI_MODEL_H

#include "ReversiViewInterface.h"
#include "Board.h"
#include "Turn.h"
#include <vector>
#include <stack>

class Turn;
struct ValidMove;

class ReversiModel
{
	Board b_;

	// a vector full of all boardsquares on the board that do not have the state EMPTY
	std::vector<BoardSquare> non_empty_bs_vector_;

	// a vector full of all boardsquares adjacent to all non-empty board squares
	std::vector<BoardSquare> adjacent_empty_bs_vector_;

	// the current player turn.
	Turn* p_t_;

	// it is set to true when the game is over, which is when there is no more moves that either player can make.
	bool game_over_flag_;

	// holds the address to each view that has been registered with ReversiModel
	std::vector<ReversiViewInterface*> rvi_addr_vector_;



	/************************checkMove************************************
	* When a user submits a move, this function is called to check to see whether its
	* valid or not.
	* Parameters:
	*	 Turn t: the current turn
	*    int row: coordinate of chosen board square
	*    int col: other coordinate of chosen board square
	* Returns:
	*    bool: true if the move is valid, false if it is not.
	*
	***************************************************************************/
	bool checkMove(int row, int col);

	
	/************************updateNonEmptyBoardSquareVector************************************
	* Updates the non empty board square vector to add the last move that was made and to update
	* the other squares that may have been changed (had their state changed from WHITE to BLACK or vice-versa)
	* as a result of a player move.
	* the player made
	* Parameters:
	*	 BoardSquare chosen_bs: the move that a player had just made.
	*    State pc: the player colour of the player who just moved.
	* Returns:
	*    void
	*
	*******************************************************************/
	void updateNonEmptyBoardSquareVector(BoardSquare chosen_bs, State pc);

	
	/************************updateAdjacentEmptyBoardSquareVector************************************
	* Updates the adjacent empty board square vector to add squares that have recently become adjacent due to the last move
	* the player made
	* Parameters:
	*	 BoardSquare chosen_bs: the move that a player had just made.
	* Returns:
	*    void
	*
	*******************************************************************/
	void updateAdjacentEmptySquares(BoardSquare bs);

	
	/************************getChosenValidMove************************************
	* Matches the chosen move to the array of possible valid moves for the turn.
	* Returns false if the move is invalid.
	* Parameters:
	*     int row: row of the chosen move
	*	  int col: column of the chosen move
	*     ValidMove* p_chosen_vm: pointer to the chosen ValidMove
	* Returns:
	*     bool
	*
	*******************************************************************/
	bool getChosenValidMove(int row, int col, ValidMove* p_chosen_vm);


	/************************resolveMove************************************
	* The player has made a move and this function resolves the outcome of that move.
	* If the move results in the game ending, it detects that and sets the appropriate flag.
	* It also updates the board.
	* Parameters:
	*	 BoardSquare chosen_bs: the move that a player had just made.
	* Returns:
	*    void
	*
	*******************************************************************/
	void resolveMove(BoardSquare chosen_bs);

	
	/************************flipBoardSquares************************************
	* Called by resolveMove, when a move is made, this is the function that actually changes
	* the states of the squares on the board as a result of the move.
	* Parameters:
	*	 int chosen_bs_row: the row of a move that a player had just made.
	*    int chosen_bs_col: the column of a move that a player had just made.
	*    State pc: the player colour
	*    Board* p_b: the board
	*    int row_offset: used to determine which direction that pieces are being captured in
	*    int col_offset: used to determine which direction that pieces are being captured in
	* Returns:
	*    void
	*
	*******************************************************************/
	void flipBoardSquares(int chosen_bs_row, int chosen_bs_col, State pc, Board* p_b, int row_offset, int col_offset);

	
	/************************notifyView************************************
	* resolveMove() calls this function at the end to let all the classes that implemented
	* ReversiViewInterface and registered with ReversiModel to update the UI.
	* Parameters:
	*	 None
	* Returns:
	*    void
	*
	*******************************************************************/
	void notifyView();

    public:

		/************************ReversiModel************************************
		* Constructor. Initializes the board, sets up the first turn, and initializes
		* the vector attributes.
		*
		*******************************************************************/
		ReversiModel();

		
		/************************~ReversiModel************************************
		* Destructor. Deletes the Turn pointer.
		*
		*******************************************************************/
		~ReversiModel();

		
		/************************getBoardSquareState************************************
		* Returns the state of a chosen board square
		* Parameters:
		*    int row: the row of the desired board square
		*    int col: the column of the desired board square
		* Returns:
		*    State: the state of the desired board square
		*
		*******************************************************************/
		State getBoardSquareState(int row, int col);

		
		/************************chooseBoardSquare************************************
		* The board square chosen is the next move.
		* Parameters:
		*    int row: the row of the desired board square
		*    int col: the column of the desired board square
		* Returns:
		*    bool: returns false if the move chosen is not valid. Returns true if it is
		*
		*******************************************************************/
		bool chooseBoardSquare(int row, int col);


		/************************getCurrentPlayerColour************************************
		* Returns the colour/state of the player (either BLACK or WHITE)
		* Parameters:
		*    None
		* Returns:
		*    string
		*
		*******************************************************************/
		std::string getCurrentPlayerColour();

		
		/************************isGameOver************************************
		* Returns game_over_flag_. Returns true if the game is over.
		* Parameters:
		*    None
		* Returns:
		*    bool
		*
		*******************************************************************/
		bool isGameOver();

		
		/************************getScore************************************
		* Returns the score. The first value is how many points the BLACK player has,
		* the second value is how many points the WHITE player has
		* Parameters:
		*    None
		* Returns:
		*    pointer to int[2]
		*
		*******************************************************************/
		int* getScore();

		
		/************************registerView************************************
		* This member function is used by a class implementing the ReversiViewInterface 
		* to register with ReversiModel so that ReversiModel can call its updateView() 
		* member function.
		* Parameters:
		*    ReversiViewInterface* p_rvi: pointer to reversiViewInterface
		* Returns:
		*    bool
		*
		*******************************************************************/
		void registerView (ReversiViewInterface* p_rvi);

		
		/************************removeView************************************
		* This member function is used by a class implementing the ReversiViewInterface 
		* to unregister with ReversiModel and stop recieving updateView() calls. 
		* Parameters:
		*    ReversiViewInterface* p_rvi: pointer to reversiViewInterface
		* Returns:
		*    bool
		*
		*******************************************************************/
		void removeView (ReversiViewInterface* p_rvi);


};

#endif // REVERSI_MODEL_H