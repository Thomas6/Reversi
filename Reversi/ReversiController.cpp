#include "CppInterfaces.h"

#include "ReversiController.h"
#include "ReversiViewConsole.h"
#include <stdlib.h>
#include <string>

ReversiController::ReversiController()
{
	ReversiModel* p_rm = new ReversiModel();
	p_rm_ = p_rm;
	ReversiViewConsole rvc = ReversiViewConsole(p_rm_);

	std::string response;
	int row;
    int col;
	bool valid_move_was_chosen;

	std::cout << "The game has started. Good luck players!" << std::endl;
	std::cout << "To move, type in two numbers like \" 34 \" indicating the space that is on row 3 and column 4." << std::endl;
	std::cout << "To stop playing and exit the application, type in \"exit\"." << std::endl;
	std::cout << "BLACK player's turn. What do you want to do?" << std::endl << std::endl;
	rvc.outputBoard();
	while (!p_rm_->isGameOver())
	{
		std::cin >> response;
		// turn the characters into the integers they represent
		bool has_only_digits = (response.find_first_not_of( "0123456789" ) == std::string::npos);
		if (has_only_digits)
		{
			// converts the response into integers
			// 48 is the difference between the ascii character and the numbers they represent
			row = ((int)response.at(0)) - 48;
		    col = ((int)response.at(1)) - 48;

			std::cout << "The " <<  (std::string)p_rm_->getCurrentPlayerColour() << " player has chosen: " << "Row "<< row << " Column " << col << std::endl;
			valid_move_was_chosen = chooseBoardSquare(row, col);
			if (valid_move_was_chosen == false)
			{
				std::cout << "The move chosen was invalid. Please enter another move." << std::endl;
			}
		}
		else if (response == "exit")
		{
			break;
		}
		else
		{
			std::cout << response << std::endl;
			std::cout << "Invalid response. Please enter another response." << std::endl;
		}
	}
}

ReversiController::~ReversiController()
{
	delete p_rm_;
}

bool ReversiController::chooseBoardSquare(int row, int col)
{
	return p_rm_->chooseBoardSquare(row, col);
}