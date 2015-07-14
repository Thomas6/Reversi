#ifndef REVERSI_VIEW_H
#define REVERSI_VIEW_H

//#pragma once
//#include "ReversiView.fwd.h"
//#include "ReversiModel.fwd.h"

//#include "ReversiModel.h"
//#include "ReversiViewInterface.h"

class ReversiView// : implements ReversiViewInterface
{
	protected:

	    //ReversiModel* p_rm_;

    public:

		ReversiView();
		//ReversiView(ReversiModel* p_rm_); 
		~ReversiView() {}

    public:

	    // 
		//virtual void outputScore();

	    // output board to console
	    //virtual void outputBoard();

		// check if game is over, then output
		// who won and who lost.
		//virtual void outputGameOver();

		// ReversiModel will call this function
		// after it executes resolveMove()
		//virtual void updateView();
};

#endif // REVERSI_VIEW_H