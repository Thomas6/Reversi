#include <iostream>
#include "ReversiModel.h"

//using namespace std;

int main(int argc, char **argv)
{
    std::cout << "Hello World!" << std::endl;
	std::cin.get();

	//initialize the board
	//Board board = Board();
	ReversiModel reversiModel = ReversiModel(Board());
	reversiModel.resolveMove(reversiModel.getBoardAddr(), *reversiModel.getBoardAddr()->getBoardSquare(3, 4), reversiModel.getTurnAddr());
	return 0;
}