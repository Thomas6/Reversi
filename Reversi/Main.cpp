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
	return 0;
}