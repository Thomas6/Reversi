#include "ReversiModel.h"
#include <iostream>

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

	p_t_ = new Turn(BLACK, adjacent_empty_bs_vector_, b_);

	invalid_move_count_ = 0;
	game_over_flag_ = false;

	// debugging!
	outputBoardToConsole();
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
	return p_t_;
}

bool ReversiModel::isGameOver()
{
	// in order to determine if the game is over, we have to hit a point
	// where there are no valid moves for two turns in a row. So we need to put
	// in some kind of counter such that when valid moves is calculated and
	// we find that it equals 0 twice in a row, isGameOver returns true
	// and the game is over ie. no more moves can be made and a winner is
	// declared
	return game_over_flag_;
}

int* ReversiModel::getScore()
{
	int* p_score = new int[2];
	// p_score[0] is the black player's score
	p_score[0] = 0;
	// p_score[1] is the white player's score
	p_score[1] = 0;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (b_.getBoardSquare(i, j)->getState() == BLACK)
			{
				p_score[0]++;
			}
			if (b_.getBoardSquare(i, j)->getState() == WHITE)
			{
				p_score[1]++;
			}
		}
	}
	return p_score;
}

void ReversiModel::updateNonEmptyBoardSquareVector(BoardSquare chosen_bs, State pc)
{
	// compare all the bs's in non_empty_bs_vector with the bs's on the board
	// if they have different states change the ones in the vector to have the state they are on the board
	for (int i = 0; i < (int)non_empty_bs_vector_.size(); i++)
	{
		non_empty_bs_vector_[i].setState( b_.getBoardSquare( non_empty_bs_vector_[i].getRow(), non_empty_bs_vector_[i].getCol() )->getState() );
	}
	chosen_bs.setState(pc);
	non_empty_bs_vector_.push_back(chosen_bs);
}

void ReversiModel::updateAdjacentEmptySquares(BoardSquare bs)
{
	// check all 8 adjacent squares to the current squares and add them to adjacent_empty_bs_vector
	BoardSquare possible_empty_bs; //  = *board.getBoardSquare(boardSquare.getRow(), boardSquare.getColumn());
	int bs_row = bs.getRow();
	int bs_col = bs.getCol();
	int adjacent_empty_bs_vector_size = adjacent_empty_bs_vector_.size();
	bool add_flag;

	for (int i = 0; i < 8; i++)
	{
		possible_empty_bs = *b_.getBoardSquare
		(
			bs_row + p_t_->getCardinalAndOrdinalDirectionsArray()[i].row_offset,
			bs_col + p_t_->getCardinalAndOrdinalDirectionsArray()[i].col_offset
		);
		add_flag = true;
		for (int i = 0; i < adjacent_empty_bs_vector_size; i++)
		{
			// if its already in adjacent empty board square vector, or if its non-empty, don't add it
			if (adjacent_empty_bs_vector_[i].getRow() == possible_empty_bs.getRow() &&
				adjacent_empty_bs_vector_[i].getCol() == possible_empty_bs.getCol() ||
				possible_empty_bs.getState() != EMPTY)
			{
				add_flag = false;
				break;
			}
		}
		// if it isn't, go ahead and add it
		if (add_flag == true)
		{
			adjacent_empty_bs_vector_.push_back(possible_empty_bs);
			add_flag = false;
		}
	}
}

//split into two functions
bool getChosenValidMove(Turn t, int row, int col, ValidMove* p_chosen_vm)
{
	for (int i = 0; i < t.getValidMoveArraySize(); i++)
	{
		if (row == t.getValidMoveArray()[i].row && col == t.getValidMoveArray()[i].col)
		{
			*p_chosen_vm = t.getValidMoveArray()[i];
			return true;
		}
	}
	return false;
}

bool checkMove(Turn t, int row, int col)
{
	for (int i = 0; i < t.getValidMoveArraySize(); i++)
	{
		if (row == t.getValidMoveArray()[i].row && col == t.getValidMoveArray()[i].col)
		{
			return true;
		}
	}
	return false;
}

// don't forget to change getBoardSquare to verify if it returns an offBoard boardsquare.
void ReversiModel::resolveMove(BoardSquare chosen_bs)
{
	ValidMove* p_vm = p_t_->getValidMoveArray();
	ValidMove chosen_vm;
	int chosen_bs_row = chosen_bs.getRow();
	int chosen_bs_col = chosen_bs.getCol();
	State pc = p_t_->getPlayerColour();
	bool is_chosen_mv_flag = getChosenValidMove(*p_t_, chosen_bs_row, chosen_bs_col, &chosen_vm);

	if (is_chosen_mv_flag == false)
	{
		invalid_move_count_++;
		return;
	}
	// if the user picks an invalid move, nothing happens.
	else
	{
		invalid_move_count_ = 0;
	}

	if (invalid_move_count_ >= 2)
	{
		// notfiy the view and stop the game?
		game_over_flag_ = true;
		return;
	}

	for (int i = 0; i < chosen_vm.dir_name_array_size; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (p_t_->getCardinalAndOrdinalDirectionsArray()[j].dir_name == chosen_vm.p_dir_name_array[i])
			{
				flipBoardSquares(chosen_bs_row, chosen_bs_col, pc, &b_, p_t_->getCardinalAndOrdinalDirectionsArray()[j].row_offset,
					                                                    p_t_->getCardinalAndOrdinalDirectionsArray()[j].col_offset);
			}
		}
	}
	
	// update adjacent empty board squares
	for (int i = 0; i < (int)adjacent_empty_bs_vector_.size(); i++)
	{
		// figure out how to do this
		if (adjacent_empty_bs_vector_[i].getRow() == chosen_bs.getRow() && adjacent_empty_bs_vector_[i].getCol() == chosen_bs.getCol())
		{
			// hope this doesn't erase the wrong thing.
			adjacent_empty_bs_vector_.erase(adjacent_empty_bs_vector_.begin() + i);
			break;
		}
	}
	// update non empty board squares
	updateNonEmptyBoardSquareVector(chosen_bs, p_t_->getPlayerColour());

	// update empty adjacent board squares
	updateAdjacentEmptySquares(chosen_bs);

	//
	outputBoardToConsole();

	// now, update the View and delete the turn because it is finished.
	updateView();

	pc = p_t_->getPlayerColour();

	// look up how destructors work
	delete p_t_;

	// might delegate some of this functionality to another function and make some of these functions private too
	p_t_ = new Turn( p_t_->getOtherPlayerColour(pc), adjacent_empty_bs_vector_, b_);
}

void ReversiModel::flipBoardSquares(int chosen_bs_row, int chosen_bs_col, State pc, Board* p_b, int row_offset, int col_offset)
{
	BoardSquare* p_being_changed_bs = p_b->getBoardSquare(chosen_bs_row, chosen_bs_col);

	// change the chosen board square state to the player colour.
	p_b->setBoardSquareState(p_being_changed_bs, pc);
	p_being_changed_bs = p_b->getBoardSquare(chosen_bs_row + row_offset, chosen_bs_col + col_offset);
	// now change the capture line board squares to the player colour
	while (p_being_changed_bs->getState() != pc)
	{
		// here we finally alter the board.
		p_b->setBoardSquareState(p_being_changed_bs, pc); 
		p_being_changed_bs = p_b->getBoardSquare(p_being_changed_bs->getRow() + row_offset, p_being_changed_bs->getCol() + col_offset);
	}
}

void ReversiModel::updateView(){}

void ReversiModel::outputBoardToConsole()
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			std::cout << b_.getBoardSquare(i, j)->getState();
			// if end of row, go to next row
			if (j == 8)
			{
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
}