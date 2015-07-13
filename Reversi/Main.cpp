#include <iostream>
#include "ReversiModel.h"

//using namespace std;

int main(int argc, char **argv)
{
	//initialize the model
	ReversiModel reversiModel = ReversiModel(Board());
	reversiModel.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 4));
	reversiModel.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 5));
	reversiModel.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 6));
	reversiModel.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(2, 5));
	reversiModel.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(5, 6));
	reversiModel.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 7));
	return 0;
}