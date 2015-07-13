#include <iostream>
#include "ReversiModel.h"

//using namespace std;

int main(int argc, char **argv)
{
	//initialize the model
	ReversiModel rm;
	rm.chooseBoardSquare(3, 4);
	rm.chooseBoardSquare(3, 5);
	rm.chooseBoardSquare(3, 6);
	rm.chooseBoardSquare(2, 5);
	rm.chooseBoardSquare(5, 6);
	rm.chooseBoardSquare(3, 7);
	// this move shouldn't take
	rm.chooseBoardSquare(1, 1);
	/*
	rm.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 4));
	rm.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 5));
	rm.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 6));
	rm.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(2, 5));
	rm.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(5, 6));
	rm.resolveMove(*reversiModel.getBoardAddr()->getBoardSquare(3, 7));
	*/
	return 0;
}