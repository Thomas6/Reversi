#ifndef REVERSI_VIEW_CONSOLE_H
#define REVERSI_VIEW_CONSOLE_H

#include "ReversiModel.h"
#include <iostream>
#include <string>

class ReversiViewConsole : implements ReversiViewInterface
{
	ReversiModel* p_rm_;

    public:

		/************************ReversiViewConsole************************************
		* Default constructor for ReversiViewConsole.
		* Parameters:
		*    None.
		* Returns:
		*    ReversiViewConsole
		*
		*******************************************************************/
		ReversiViewConsole(){}


		/************************ReversiViewConsole************************************
		* Constructor for ReversiViewConsole. Sets the ReversiModel pointer attribute for
		* the class. It also registers the class with the model. The idea is that ReversiModel
		* could display multiple views if desired.
		* Parameters:
		*    ReversiModel*
		* Returns:
		*    ReversiViewConsole
		*
		*******************************************************************/
		ReversiViewConsole(ReversiModel* p_rm);


		/************************outputScore************************************
		* Calls getScore() from ReversiModel, then outputs it to console.
		* Parameters:
		*    None
		* Returns:
		*    void
		*
		*******************************************************************/
		void outputScore();


		/************************outputBoard************************************
		* Outputs the current board state.
		* Parameters:
		*    None
		* Returns:
		*    void
		*
		*******************************************************************/
		void outputBoard();

		
		/************************outputBoard************************************
		* Calls isGameOver() from ReversiModel and outputs to console if true.
		* Outputs different text depending on who won.
		* Parameters:
		*    None
		* Returns:
		*    void
		*
		*******************************************************************/
		void outputGameOver();


		/************************updateView************************************
		* Implements updateView from the ReversiViewInterface.
		* It calls outputScore, outputBoard and outputGameOver when called.
		* Parameters:
		*    None
		* Returns:
		*    void
		*
		*******************************************************************/
		void updateView();
};

#endif // REVERSI_VIEW_CONSOLE_H