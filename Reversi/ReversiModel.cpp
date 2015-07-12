#include "ReversiModel.h"
#include <iostream>

Direction CARDINAL_AND_ORDINAL_DIRECTIONS[8];
int p_vm_array_size;

ReversiModel::ReversiModel(Board board)
{
	b_ = board;
	// the initial board configuration
	non_empty_bs_vector_.push_back(BoardSquare(4, 4, BLACK));
	non_empty_bs_vector_.push_back(BoardSquare(4, 5, WHITE));
	non_empty_bs_vector_.push_back(BoardSquare(5, 4, WHITE));
	non_empty_bs_vector_.push_back(BoardSquare(5, 5, BLACK));

	// the initial empty boardsquares adjacent to the starting pieces
	adjacent_empty_bs_vector_.push_back(BoardSquare(3, 3, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(3, 4, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(3, 5, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(3, 6, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(4, 6, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(5, 6, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(6, 6, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(6, 5, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(6, 4, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(6, 3, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(5, 3, EMPTY));
	adjacent_empty_bs_vector_.push_back(BoardSquare(4, 3, EMPTY));

	Turn* p_turn = new Turn(getValidMoves(b_, BLACK, adjacent_empty_bs_vector_), BLACK);
	p_turn_ = p_turn;

	constructDirectionArray();

	outputBoardToConsole(getBoardAddr());
}

void ReversiModel::constructDirection(Direction &dir, int row_offset, int col_offset, Direction_Name dir_name)
{
	dir.row_offset = row_offset;
	dir.col_offset = col_offset;
	dir.dir_name = dir_name;
}

void ReversiModel::constructDirectionArray()
{
	Direction dir;
	constructDirection(dir, 0, -1, LEFT);
	CARDINAL_AND_ORDINAL_DIRECTIONS[0] = dir;
	constructDirection(dir, -1, -1, UP_LEFT);
	CARDINAL_AND_ORDINAL_DIRECTIONS[1] = dir;
	constructDirection(dir, -1, 0, UP);
	CARDINAL_AND_ORDINAL_DIRECTIONS[2] = dir;
	constructDirection(dir, -1, 1, UP_RIGHT);
	CARDINAL_AND_ORDINAL_DIRECTIONS[3] = dir;
	constructDirection(dir, 0, 1, RIGHT);
	CARDINAL_AND_ORDINAL_DIRECTIONS[4] = dir;
	constructDirection(dir, 1, 1, DOWN_RIGHT);
	CARDINAL_AND_ORDINAL_DIRECTIONS[5] = dir;
	constructDirection(dir, 1, 0, DOWN);
	CARDINAL_AND_ORDINAL_DIRECTIONS[6] = dir;
	constructDirection(dir, 1, -1, DOWN_LEFT);
	CARDINAL_AND_ORDINAL_DIRECTIONS[7] = dir;
}

Board* ReversiModel::getBoardAddr()
{
	return &b_;
}

std::vector<BoardSquare>* ReversiModel::getNonEmptyBoardSquareVectorAddr()
{
	return &non_empty_bs_vector_;
}

std::vector<BoardSquare>* ReversiModel::getAdjacentEmptyBoardSquareVectorAddr()
{
	return &adjacent_empty_bs_vector_;
}

Turn* ReversiModel::getTurnAddr()
{
	return p_turn_;
}

void ReversiModel::setValidMove(int row, int col, Direction_Name* dirs, int numDirs, ValidMove* p_vm)
{
	p_vm->row = row;
	p_vm->col = col;
	p_vm->p_dirs = dirs;
	p_vm->p_dirs_size = numDirs;
}

// use a blob finder algorithm? Should be faster. use a growing vector of possible moves/empty spaces rather than searching the board over and over.
//********************** TODO *************************
// make direction a struct and remove some repition?
// this isn't working; it's including non-empty boardsquares
void ReversiModel::getAdjacentEmptySquares(Board b, BoardSquare bs, std::vector<BoardSquare>* p_adjacent_empty_bs_vector)
{
	// check all 8 adjacent squares to the current squares and add them to adjacent_empty_bs_vector
	BoardSquare possible_empty_bs; //  = *board.getBoardSquare(boardSquare.getRow(), boardSquare.getColumn());
	int bs_row = bs.getRow();
	int bs_col = bs.getCol();
	int adjacent_empty_bs_vector_size = p_adjacent_empty_bs_vector->size();
	bool add_flag;

	for (int i = 0; i < 8; i++)
	{
		possible_empty_bs = *b.getBoardSquare
		(
			bs_row + CARDINAL_AND_ORDINAL_DIRECTIONS[i].row_offset,
			bs_col + CARDINAL_AND_ORDINAL_DIRECTIONS[i].col_offset
		);
		add_flag = true;
		for (int i = 0; i < adjacent_empty_bs_vector_size; i++)
		{
			// if its already in adjacent empty board square vector, or if its non-empty, don't add it
			if ((*p_adjacent_empty_bs_vector)[i].getRow() == possible_empty_bs.getRow() &&
				(*p_adjacent_empty_bs_vector)[i].getCol() == possible_empty_bs.getCol() ||
				possible_empty_bs.getState() != EMPTY)
			{
				add_flag = false;
				break;
			}
		}
		// if it isn't, go ahead and add it
		if (add_flag == true)
		{
			p_adjacent_empty_bs_vector->push_back(possible_empty_bs);
			add_flag = false;
		}
	}
}

State ReversiModel::getOtherPlayerColour(State pc)
{
	if(pc == BLACK)
	{
		return WHITE;
	}
	else // playerColour is white
	{
		return BLACK;
	}
}

bool ReversiModel::checkDirection(BoardSquare current_empty_bs, Board b, State pc, int row_offset, int col_offset)
{
	BoardSquare* p_examined_bs;

	p_examined_bs = b.getBoardSquare(current_empty_bs.getRow() + row_offset, current_empty_bs.getCol() + col_offset);
	// if the board square being examined is of the other player's colour, then there is the potential for a move in this direction
	if (p_examined_bs->getState() == getOtherPlayerColour(pc))
	{
		// now we check the board square beyond this one to see if it is a valid move 
		p_examined_bs = b.getBoardSquare(p_examined_bs->getRow() + row_offset, p_examined_bs->getCol() + col_offset);
		// if it is of the current player's colour, then this is definitely a valid move
		if (p_examined_bs->getState() == pc)
		{
			return true;
		}
		// if it is yet another board square of the other player's colour...
		else if (p_examined_bs->getState() == getOtherPlayerColour(pc))
		{
			// ...we must keep on going until we find a board square that is either of our colour or something else
			while(p_examined_bs->getState() == getOtherPlayerColour(pc))
			{
				p_examined_bs = b.getBoardSquare(p_examined_bs->getRow() + row_offset, p_examined_bs->getCol() + col_offset);
				// if we found a board square that is of the current player's colour, then this is definitely a valid move
				if (p_examined_bs->getState() == pc)
				{
					return true;
		        }
				// if we found a board square that is either empty or off board, then we go on to the next direction
				else if (p_examined_bs->getState() == EMPTY || OFFBOARD)
				{
					return false;
				}
			}
		}
		// if its not either player colour, then the examined board square is empty or off board, and we must look in a different direction
		else
		{
			 return false;
		}
	}
	// if the board square being examined is not of the other player's colour, then we go on to the next direction
	else
	{
		return false;
	}
}

ValidMove ReversiModel::getValidMove(BoardSquare current_empty_bs, Board b, State pc)
{
	// maybe do this better later as well?
	// store the directions for a valid move somewhere while we determine the capture line directions
	ValidMove vm;
	int tempDirs[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	// check left
	if(checkDirection(current_empty_bs, b, pc, 0, -1))
	{
		tempDirs[0] = LEFT;
	}
	// check up left
	else if (checkDirection(current_empty_bs, b, pc, -1, -1))
	{
		tempDirs[1] = UP_LEFT;
	}
	// check up
	else if (checkDirection(current_empty_bs, b, pc, -1, 0))
	{
		tempDirs[2] = UP;
	}
	// check up right
	else if (checkDirection(current_empty_bs, b, pc, -1, 1))
	{
		tempDirs[3] = UP_RIGHT;
	}
	// check right
	else if (checkDirection(current_empty_bs, b, pc, 0, 1))
	{
		tempDirs[4] = RIGHT;
	}
	// check down right
	else if (checkDirection(current_empty_bs, b, pc, 1, 1))
	{
		tempDirs[5] = DOWN_RIGHT;
	}
	// check down
	else if (checkDirection(current_empty_bs, b, pc, 1, 0))
	{
		tempDirs[6] = DOWN;
	}
	// check down left
	else if (checkDirection(current_empty_bs, b, pc, 1, -1))
	{
		tempDirs[7] = DOWN_LEFT;
	}
	else
	{

	}

	// find the number of directions for possible line captures for the valid move
	int numDirs = 0;
	for (int i = 0; i < 8; i++)
	{
		if (tempDirs[i] != -1)
		{
			numDirs++;
		}
	}
	Direction_Name* dirs = new Direction_Name[numDirs];
	// also, code this better? it looks weird.
	// assign the line captures to dir
	int j = 0;
	for (int i = 0; i < 8; i++)
	{
		if (tempDirs[i] != -1)
		{
			dirs[j] = (Direction_Name)tempDirs[i];
			j++;
		}
	}

	setValidMove(current_empty_bs.getRow(), current_empty_bs.getCol(), dirs, numDirs, &vm);
	return vm;
}

ValidMove* ReversiModel::getValidMoves(Board b, State pc, std::vector<BoardSquare> adjacent_empty_bs_vector)
{
	BoardSquare current_empty_bs;
	std::stack<ValidMove> temp_vm_stack;
	ValidMove vm;
	// not sure I need this
	ValidMove* p_vm_array;

	while (!adjacent_empty_bs_vector.empty())
	{
	    current_empty_bs = adjacent_empty_bs_vector.back();
		vm = getValidMove(current_empty_bs, b, pc);
		if (vm.p_dirs_size != 0)
		{
			temp_vm_stack.push(vm);
		}
		adjacent_empty_bs_vector.pop_back();
	}
	// hope this doesn't break anything
	// not sure I need this
	//delete p_temp_vm;

	p_vm_array = new ValidMove[temp_vm_stack.size()];
	p_vm_array_size = temp_vm_stack.size();
	//p_vm_array->p_dirs_size = temp_vm_stack.size();

	for (int i = 0; !temp_vm_stack.empty(); i++)
	{
		p_vm_array[i] = temp_vm_stack.top();
		temp_vm_stack.pop();
	}
	// more debugging!
	/* debugging!
	ValidMove move1 = p_ValidMoves[0];
	ValidMove move2 = p_ValidMoves[1];
	ValidMove move3 = p_ValidMoves[2];
	ValidMove move4 = p_ValidMoves[3];
	*/
	return p_vm_array;
}
// should be passing board address, not pointer
void ReversiModel::updateNonEmptyBoardSquareVector(Board* p_b, std::vector<BoardSquare>* p_non_empty_bs_vector, BoardSquare chosen_bs, State pc)
{
	// compare all the bs's in non_empty_bs_vector with the bs's on the board
	// if they have different states change the ones in the vector to have the state they are on the board
	for (int i = 0; i < (int)p_non_empty_bs_vector->size(); i++)
	{
		(*p_non_empty_bs_vector)[i].setState( p_b->getBoardSquare( (*p_non_empty_bs_vector)[i].getRow(), (*p_non_empty_bs_vector)[i].getCol() )->getState() );
	}
	chosen_bs.setState(pc);
	p_non_empty_bs_vector->push_back(chosen_bs);
}

// don't forget to change getBoardSquare to verify if it returns an offBoard boardsquare.
void ReversiModel::resolveMove(Board* p_b, BoardSquare chosen_bs, Turn* p_turn, std::vector<BoardSquare>* p_adjacent_empty_bs_vector, std::vector<BoardSquare>* p_non_empty_bs_vector)
{
	//******************************* for debugging purposes; create function checkMove
	ValidMove* p_vm = p_turn->getValidMoves();
	//int p_vm_array_size = p_turn->getValidMoveArraySize();
	ValidMove chosen_vm;
	Direction_Name* p_dirs;
	int chosen_bs_row = chosen_bs.getRow();
	int chosen_bs_col = chosen_bs.getCol();
	State pc = p_turn->getPlayerColour();
	/*
	while (p_vm != NULL)
	{
		if (chosen_bs_row == p_vm->row && chosen_bs_col == p_vm->col)
		{
			chosen_vm = *p_vm;
			break;
		}
		p_vm++;
	}
	*/
	
	for (int i = 0; i < p_vm_array_size; i++)
	{
		if (chosen_bs_row == p_vm[i].row && chosen_bs_col == p_vm[i].col)
		{
			chosen_vm = p_vm[i];
			break;
		}
	}
	
	ValidMove vm1 = p_vm[0];
	ValidMove vm2 = p_vm[1];
	ValidMove vm3 = p_vm[2];

	/*
	while (p_vm != NULL)
	{
		if (chosen_bs_row == p_vm->row && chosen_bs_col == p_vm->col)
		{
			chosen_vm = *p_vm;
			break;
		}
		p_vm++;
	}
	*/
	//*************************

	p_dirs = chosen_vm.p_dirs;
	// make this not fuck up
	for (int i = 0; p_dirs[i] != NULL; i++)
	{
		int integer = p_dirs[i];
		switch (p_dirs[i])
		{
		    case LEFT:	
                flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, 0, -1);
				break;
			case UP_LEFT:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, -1, -1);
				break;
			case UP:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, -1, 0);
				break;
			case UP_RIGHT:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, -1, 1);
				break;
			case RIGHT:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, 0, 1);
				break;
			case DOWN_RIGHT:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, 1, 1);
				break;
			case DOWN:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, 1, 0);
				break;
			case DOWN_LEFT:
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, p_b, 1, -1);
				break;
		}
	}

	// update adjacent empty board squares
	for (int i = 0; i < (int)p_adjacent_empty_bs_vector->size(); i++)
	{
		// figure out how to do this
		if ((*p_adjacent_empty_bs_vector)[i].getRow() == chosen_bs.getRow() && (*p_adjacent_empty_bs_vector)[i].getCol() == chosen_bs.getCol())
		{
			// hope this doesn't erase the wrong thing.
			p_adjacent_empty_bs_vector->erase(p_adjacent_empty_bs_vector->begin() + i);
			break;
		}
	}
	// update non empty board squares
	updateNonEmptyBoardSquareVector(p_b, p_non_empty_bs_vector, chosen_bs, p_turn->getPlayerColour());

	//non_empty_bs_vector.push_back(chosen_bs);

	// update empty adjacent board squares
	getAdjacentEmptySquares(*p_b, chosen_bs, p_adjacent_empty_bs_vector);

	BoardSquare square1 = *p_b->getBoardSquare(3, 4);
	BoardSquare square2 = *p_b->getBoardSquare(4, 4);
	BoardSquare square3 = *p_b->getBoardSquare(5, 4);
	BoardSquare square4 = *p_b->getBoardSquare(4, 5);
	BoardSquare square5 = *p_b->getBoardSquare(5, 5);

	outputBoardToConsole(p_b);

	// now, update the View and delete the turn because it is finished.
	updateView();

	pc = p_turn->getPlayerColour();
	// look up how destructors work
	delete p_turn;

	// might delegate some of this functionality to another function and make some of these functions private too
	p_turn = new Turn(getValidMoves(*p_b, getOtherPlayerColour(pc), *p_adjacent_empty_bs_vector), getOtherPlayerColour(pc));
	p_turn_ = p_turn;
}
// change column to col
void ReversiModel::flipBoardSquares(int chosen_bs_row, int chosen_bs_col, State pc, Board* p_b, int row_offset, int col_offset)
{
	BoardSquare* p_being_changed_bs = p_b->getBoardSquare(chosen_bs_row, chosen_bs_col);
	while (p_being_changed_bs->getState() != pc)
	{
		// here we finally alter the board.
		p_b->setBoardSquareState(p_being_changed_bs, pc); 
		p_being_changed_bs = p_b->getBoardSquare(chosen_bs_row + row_offset, chosen_bs_col + col_offset);
	}
}

void ReversiModel::updateView(){}

void ReversiModel::outputBoardToConsole(Board* p_b)
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			std::cout << p_b->getBoardSquare(i, j)->getState();
			// if end of row, go to next row
			if (j == 8)
			{
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
}