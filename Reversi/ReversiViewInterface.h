#ifndef REVERSI_VIEW_INTERFACE_H
#define REVERSI_VIEW_INTERFACE_H

#include "CppInterfaces.h"

DeclareInterface(ReversiViewInterface)

	/**************updateView***************************************************************
	* This function is called by notifyView in the ReversiModel class and
	* the implementation of this function (and thus this interface) should update the view.
	* Parameters:
	*    None
	* Returns:
	*    Void
	*
	**************************************************************************************/
	virtual void updateView() = 0;
EndInterface

#endif // REVERSI_VIEW_INTERFACE_H