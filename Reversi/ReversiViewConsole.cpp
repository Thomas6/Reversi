#include "CppInterfaces.h"

#include "ReversiViewConsole.h"

ReversiViewConsole::ReversiViewConsole(ReversiModel* p_rm)
{
	p_rm_ = p_rm;
	p_rm->registerView(this);
}

void ReversiViewConsole::outputScore()
{
	int black_score = p_rm_->getScore()[0];
	int white_score = p_rm_->getScore()[1];
	std::cout << "Black has " << black_score << " points." << std::endl;
    std::cout << "White has " << white_score << " points." << std::endl;

	if (p_rm_->isGameOver() == false)
	{
		std::cout << (std::string)p_rm_->getCurrentPlayerColour() << " player's turn." << std::endl << std::endl;
	}
	else
	{
		std::cout << std::endl;
	}
}

// make this better
void ReversiViewConsole::outputBoard()
{
	for (int i = 0; i <= 16; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (i == 0 && j == 1)
			{
				std::cout << " ";
			}
			if (i == 0 && j != 1)
			{
				std::cout << j - 1;
				if (j == 8)
				{
					std::cout << " " << j;
				}
			}
			if (i % 2 == 0 && i != 0)
			{
				if (j == 1)
				{
					std::cout << i/2 << " ";
				}
				// change this so that it outputs letters and add spaces and lines and shit
				if ( p_rm_->getBoardSquareState(i/2, j) == EMPTY)
				{
					std::cout << "-" << " ";
				}
				else if ( p_rm_->getBoardSquareState(i/2, j) == BLACK)
				{
					std::cout << "B" << " ";
				}
				// it must be white if its not either empty or black
				else
				{
					std::cout << "W" << " ";
				}
			
				// if end of row, go to next row
				if (j == 8)
				{
					std::cout << std::endl;
				}
		    }
			else
			{
				if(j == 8)
				{
					std::cout << std::endl;
				}
				else
				{
				    std::cout << " ";
				}
			}
		}
	}
	std::cout << std::endl;
}

void ReversiViewConsole::outputGameOver()
{
	if (p_rm_->isGameOver() == true)
	{
		int black_score = p_rm_->getScore()[0];
		int white_score = p_rm_->getScore()[1];
		if (white_score > black_score)
		{
			std::cout << "White is the winner!" << std::endl;
			std::cout << "Black, you need to practice more!" << std::endl;
			std::cin.get();
			std::cin.get();
		}
		else if (white_score < black_score)
		{
			std::cout << "Black is the winner!" << std::endl;
			std::cout << "White, you need to practice more!" << std::endl;
			std::cin.get();
			std::cin.get();
		}
		// its a tie I guess?
		else
		{
			std::cout << "It's a tie! You are both well matched!" << std::endl;
			std::cin.get();
			std::cin.get();
		}
	}
	else
	{
		return;
	}
}

void ReversiViewConsole::updateView()
{
	outputScore();
	outputBoard();
	outputGameOver();
}