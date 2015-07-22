#ifndef TURN_H 
#define TURN_H

#include "ReversiModel.h"
#include <vector>

enum Direction_Name { LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT };

// this struct is used in the making of the CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY,
// which is useful for a number of functions here.
struct Direction
{
    Direction_Name dir_name;
	int row_offset;
	int col_offset;
};

// A valid move is basically a particular boardmove that captures enemy pieces.
// the row and column attributes give the location of the move, and p_dir_name_array is a pointer
// to an array of directions that the move would capture in. For example, if a particular ValidMove had an
// array with LEFT and UP in it, that move would capture pieces leftwards and upwards from its location on the board.
struct ValidMove
{
	int row;
	int col;
	int dir_name_array_size;
	Direction_Name* p_dir_name_array;
};

class Turn
{
    private:

		int p_vm_array_size_;

		// this pointer to a valid move array contains all possible valid moves for a turn. 
		ValidMove* p_vm_array_;

		// the player's colour for this Turn. Necessary for determining the possible valid moves for a turn.
		State pc_;

		Direction CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY[8];


		/************************constructValidMove************************************
		* Constructs a single valid move.
		* Parameters:
		*    BoardSquare current_empty_bs: this is a board square where there might be a potential valid move.
		*    Board b: the current state of the board
		*    State pc: the player, or the player's colour for the turn.
		* Returns:
		*    A ValidMove. If a validMove has a dir_name_array_size of 0, its actually an invalid move.
		*
		*******************************************************************/
		ValidMove constructValidMove(BoardSquare current_empty_bs, Board b, State pc);


		/************************constructDirection************************************
		* Sets the attributes in a Direction struct. Used for creating the CardinalAndOrdinalDirectionArray.
		* Parameters:
		*    Direction &dir: address to the direction struct being constructed
		*    int row_offset
		*    int col_offset
		*    Direction_Name dir_name: the name of the direction, ie. LEFT
		* Returns:
		*    void
		*
		*******************************************************************/
		void constructDirection(Direction &dir, int row_offset, int col_offset, Direction_Name dir_name);


		/************************constructCardinalAndOrdinalDirectionArray************************************
		* Constructs the CardinalAndOrdinalDirectionArray. Each value in the array is a Direction. 
		* Parameters:
		*	 None
		* Returns:
		*    void
		*
		*******************************************************************/
		void constructCardinalAndOrdinalDirectionArray();

		
		/************************checkDirection************************************
		* Used in creating a ValidMove. Checks whether a direction from a board square results in capturing
		* enemy pieces.
		* Parameters:
		*	 BoardSquare current_empty_bs: the square that might be chosen for a valid move.
		*    Board b
		*    State pc: player colour
		*    int row_offset: used to figure out which squares to travel to, ie. UP has row_offset of -1 and DOWN has row_offset of 1
		*    int col_offset
		* Returns:
		*    void
		*
		*******************************************************************/
		bool checkDirection(BoardSquare current_empty_bs, Board b, State pc, int row_offset, int col_offset);

    public:

		/************************Turn************************************
		* Constructor. Sets all the attributes.
		* Parameters:
		*	 State pc: used for setting player colour
		*    vector<BoardSquare> adjacent_empty_bs_vector: used for constructing valid moves, because 
		*        only empty squares can be valid move candidates
		*    Board b
		*
		*******************************************************************/
		Turn(State pc, std::vector<BoardSquare> adjacent_empty_bs_vector, Board b);


		/************************~Turn************************************
		* Destructor. Deletes p_vm_array_.
		*
		*******************************************************************/
		~Turn();

		
		/************************getValidMoveArraySize************************************
		* Returns the size of the valid move array. 
		* Parameters:
		*	 none
		* Returns:
		*    int
		*
		*******************************************************************/
		int getValidMoveArraySize();

		
		/************************getValidMoveArray************************************
		* Returns the valid move array. 
		* Parameters:
		*	 none
		* Returns:
		*    pointer to the valid move array (ValidMove* p_vm_array_)
		*
		*******************************************************************/
		ValidMove* getValidMoveArray();

		/************************getValidMoveArraySize************************************
		* Returns the player colour. 
		* Parameters:
		*	 none
		* Returns:
		*    State (State pc_)
		*
		*******************************************************************/
		State getPlayerColour();

		
		/************************getOtherPlayerColour************************************
		* If player colour is BLACK, it returns WHITE, and vice-versa 
		* Parameters:
		*	 State pc: the player colour
		* Returns:
		*    State 
		*
		*******************************************************************/
		State getOtherPlayerColour(State pc);

		
        /************************getCardinalAndOrdinalDirectionsArray************************************
		* Returns pointer to CARDINAL_AND_ORDINAL_DIRECTIONS_ARRAY.
		* Parameters:
		*	 none
		* Returns:
		*    pointer to Direction array
		*
		*******************************************************************/
		Direction* getCardinalAndOrdinalDirectionsArray();


};

#endif // TURN_H // end