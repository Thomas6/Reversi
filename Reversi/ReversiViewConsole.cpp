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
}

// make this better
void ReversiViewConsole::outputBoard()
{
	for (int i = 1; i <= 16; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (i % 2 == 0)
			{
				if (j == 1)
				{
					std::cout << "| ";
				}
				// change this so that it outputs letters and add spaces and lines and shit
				if ( p_rm_->getBoardSquareState(i/2, j) == EMPTY)
				{
					std::cout << "E" << " ";
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
					std::cout << "|";
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
		int white_score = p_rm_->getScore()[0];
		int black_score = p_rm_->getScore()[1];
		if (white_score > black_score)
		{
			std::cout << "White is the winner!" << std::endl;
			std::cout << "Black, you need to practice more!" << std::endl;
		}
		if (white_score < black_score)
		{
			std::cout << "Black is the winner!" << std::endl;
			std::cout << "White, you need to practice more!" << std::endl;
		}
		// its a tie I guess?
		else
		{
			std::cout << "It's a tie! You are both well matched!" << std::endl;
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