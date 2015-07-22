#include "CppInterfaces.h"

#include "ReversiModel.h"
#include <iostream>

bool ReversiModel::checkMove(int row, int col)
{
	for (int i = 0; i < p_t_->getValidMoveArraySize(); i++)
	{
		if (row == p_t_->getValidMoveArray()[i].row && col == p_t_->getValidMoveArray()[i].col)
		{
			return true;
		}
	}
	return false;
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
	BoardSquare possible_empty_bs;
	int bs_row = bs.getRow();
	int bs_col = bs.getCol();
	int adjacent_empty_bs_vector_size = adjacent_empty_bs_vector_.size();
	bool add_flag;

	// if it's equal to 0, then that means there are no more empty spaces left
	if (adjacent_empty_bs_vector_size != 0)
	{
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
}

bool ReversiModel::getChosenValidMove(int row, int col, ValidMove* p_chosen_vm)
{
	for (int i = 0; i < p_t_->getValidMoveArraySize(); i++)
	{
		if (row == p_t_->getValidMoveArray()[i].row && col == p_t_->getValidMoveArray()[i].col)
		{
			*p_chosen_vm = p_t_->getValidMoveArray()[i];
			return true;
		}
	}
	// there are no valid moves
	return false;
}

void ReversiModel::resolveMove(BoardSquare chosen_bs)
{
	ValidMove chosen_vm;
	int chosen_bs_row = chosen_bs.getRow();
	int chosen_bs_col = chosen_bs.getCol();
	State pc = p_t_->getPlayerColour();
	bool is_chosen_mv_flag = getChosenValidMove(chosen_bs_row, chosen_bs_col, &chosen_vm);

	if (is_chosen_mv_flag == false)
	{
		// something has gone horribly wrong or checkMove fouled up if it returns here
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

	pc = p_t_->getPlayerColour();

	delete p_t_;

	p_t_ = new Turn( p_t_->getOtherPlayerColour(pc), adjacent_empty_bs_vector_, b_);

	// current player can't make a move.
	if(p_t_->getValidMoveArraySize() == 0)
	{
		delete p_t_;
		p_t_ = new Turn( pc, adjacent_empty_bs_vector_, b_);
		// can the next player make a move?
		if (p_t_->getValidMoveArraySize() == 0)
		{
			// if they can't, it's game over
			game_over_flag_ = true;
		}
	}

	// calls updateView() on all views registered with ReversiModel
	notifyView();
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

// update all of the views that are registered with ReversiModel
void ReversiModel::notifyView()
{
	for (int i = 0; i < (int)rvi_addr_vector_.size(); i++)
	{
		rvi_addr_vector_[i]->updateView();
	}
}

ReversiModel::ReversiModel()
{
	b_ = Board();

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

	// the first turn
	p_t_ = new Turn(BLACK, adjacent_empty_bs_vector_, b_);

	game_over_flag_ = false;
}

ReversiModel::~ReversiModel()
{
	delete p_t_;
}

State ReversiModel::getBoardSquareState(int row, int col)
{
	return b_.getBoardSquare(row, col)->getState();
}

bool ReversiModel::chooseBoardSquare(int row, int col)
{
	bool valid_move_flag;
	valid_move_flag = checkMove(row, col);
	if (valid_move_flag == true)
	{
		resolveMove(*b_.getBoardSquare(row, col));
		return true;
	}
	else
	{
		return false;
	}
}

std::string ReversiModel::getCurrentPlayerColour()
{
	if (p_t_->getPlayerColour() == 1)
	{
		return "WHITE";
	}
	else
	{
		return "BLACK";
	}
}

bool ReversiModel::isGameOver()
{
	return game_over_flag_;
}

int* ReversiModel::getScore()
{
	int score_array[2];
	// p_score[0] is the black player's score
	score_array[0] = 0;
	// p_score[1] is the white player's score
	score_array[1] = 0;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (b_.getBoardSquare(i, j)->getState() == BLACK)
			{
				score_array[0]++;
			}
			if (b_.getBoardSquare(i, j)->getState() == WHITE)
			{
				score_array[1]++;
			}
		}
	}
	return score_array;
}

void ReversiModel::registerView (ReversiViewInterface* p_rvi)
{
	rvi_addr_vector_.push_back(p_rvi);
}

void ReversiModel::removeView (ReversiViewInterface* p_rvi)
{
	for (int i = 0; i < rvi_addr_vector_.size(); i++)
	{
        if (rvi_addr_vector_[i] == p_rvi)
		{
			rvi_addr_vector_.erase(rvi_addr_vector_.begin() + i);
		}
	}
}
