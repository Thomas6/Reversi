#include <iostream>
#include "ReversiModel.h"

//using namespace std;

int main(int argc, char **argv)
{
    std::cout << "Hello World!" << std::endl;
	std::cin.get();

	//initialize the board
	ReversiModel reversiModel = ReversiModel(Board());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(3, 4),
		reversiModel.getTurnAddr(), reversiModel.getAdjacentEmptyBoardSquareVectorAddr(), reversiModel.getNonEmptyBoardSquareVectorAddr());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(3, 5),
		reversiModel.getTurnAddr(), reversiModel.getAdjacentEmptyBoardSquareVectorAddr(), reversiModel.getNonEmptyBoardSquareVectorAddr());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(3, 6),
		reversiModel.getTurnAddr(), reversiModel.getAdjacentEmptyBoardSquareVectorAddr(), reversiModel.getNonEmptyBoardSquareVectorAddr());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(2, 5),
		reversiModel.getTurnAddr(), reversiModel.getAdjacentEmptyBoardSquareVectorAddr(), reversiModel.getNonEmptyBoardSquareVectorAddr());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(5, 6),
		reversiModel.getTurnAddr(), reversiModel.getAdjacentEmptyBoardSquareVectorAddr(), reversiModel.getNonEmptyBoardSquareVectorAddr());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(3, 7),
		reversiModel.getTurnAddr(), reversiModel.getAdjacentEmptyBoardSquareVectorAddr(), reversiModel.getNonEmptyBoardSquareVectorAddr());
	return 0;
}